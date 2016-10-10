local name = ""
local ip = ""
local flag = 1
--local ip = "192.168.0.22"
local ip = "127.0.0.1"

function love.draw()
	love.graphics.print("Welcome to BASHPONG!")
	love.graphics.print("\n")
	love.graphics.print("ip: " .. ip, 0, 20)
	love.graphics.print("Please type your name below ... ", 0, 40)
	love.graphics.print("name: " .. name, 0,60)
end

function love.keypressed( key )
	if key == 'return' then
		playing( ip, name, ipB )
	elseif key == 'backspace' then
		name = string.sub(name , 1, string.len( name  ) - 1)
	else
		name = name .. key
	end
end