#!/usr/bin/env lua

local fl = require"fltk4lua"
local socket = require"socket"


local window = fl.Window(400, 300)
  local label = fl.Box(10, 10, 380, 40, "This program listens on port 20000 and display the lines it receives below")
  label.align = fl.ALIGN_TOP + fl.ALIGN_CENTER + fl.ALIGN_WRAP + fl.ALIGN_INSIDE

  local browser = fl.Browser(10, 60, 380, 190)

  local msgb = fl.Button(10, 260, 160, 30, "Broadcast message")

  local connectb = fl.Button(180, 260, 100, 30, "Connect")

  local quitb = fl.Button(290, 260, 90, 30, "Quit")
  function quitb.callback()
    window:hide()
  end
window:end_group()
window:show(arg)

-------------------------------------------------
-- Network callbacks and server initialization --
-------------------------------------------------

local clients = {}

-- When we receive data from client
local function sk_client_cb(fd)
  local client = clients[fd]
  local data, status, rdata = client:receive"*l"
  if data or rdata ~= "" then
    browser:add(string.format("fd%d: %s", fd, data or rdata))
  end
  if status == "closed" then
    browser:add(string.format("fd%d closed by peer", fd))
    client:close()
    fl.remove_fd(fd)
    clients[fd] = nil
  end
end

-- Used when we can WRITE to a new client to know if the connection succeeded
local function sk_connect_cb(fd)
  local client = clients[fd]
  local ip, port = client:getpeername()
  if ip then
    browser:add(string.format("fd%d opened to server %s:%d", fd, ip, port))
    client:send"hello sever\n"
    fl.add_fd(fd, sk_client_cb)
  else
    fl.message"Connection failed"
    clients[fd] = nil
  end
  fl.remove_fd(fd, fl.WRITE)
end

function connectb.callback()
  local client
  local r = fl.input"Enter an client IP and port separated by a space:"
  if r then
    local ip, port = r:match"^([^ ]+) ([1-9][0-9]*)$"
    if ip and port then
      if ip:match"^[0-9a-bA-B:]+$" then -- ipv6
        client = socket.tcp6()
      elseif ip:match"^[0-9.]+$" then --ipv4
        client = socket.tcp()
      else
        fl.message"Unknown IP scheme"
        return
      end
      client:settimeout(0)
      client:connect(ip, port)
      clients[client:getfd()] = client
      fl.add_fd(client:getfd(), sk_connect_cb, fl.WRITE)
    else
      fl.message"Invalid IP:port"
      return
    end
  end
end

function msgb.callback()
  local msg = fl.input"Enter a message to send it to all clients:"
  if msg then
    for _, s in pairs(clients) do
      s:send(msg .. "\n")
    end
  end
  browser:add("broadcasted: "..msg)
end

local server = socket.bind("*", 20000)
if not server then
  error"Cannot listen on port 20000"
end

fl.add_fd(server:getfd(), function ()
  local client = server:accept()
  client:settimeout(0)
  local fd, ip, port = client:getfd(), client:getpeername()
  browser:add(string.format("fd%d opened by client at %s:%d", fd, ip, port))
  clients[fd] = client
  fl.add_fd(fd, sk_client_cb)
  client:send"hello client\n"
end)

-------------------------
-- Run the application --
-------------------------

fl.run()

-- Close the sockets, even if not needed
for _, s in pairs(clients) do
  fl.remove_fd(s:getfd())
  s:send"good bye\n"
  s:close()
end

