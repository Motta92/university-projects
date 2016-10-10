require 'libs/console'
require 'libs/math'

require 'libs/LUBE'
require 'libs/TSerial'

require 'states/main_menu'
-- HC = require 'libs/HC'
-- class = require 'libs/hump/class'
vector = require 'libs/hump/vector'

function menu()
	require 'states/menu'
end

function playing( ip, name )
	require 'states/playing'
	load( ip, name )
end

function love.load()
	gamestate = "main_menu"

	-- buttons
	button_spawn(5,200,"Start","start")
	button_spawn(5,550,"Quit", "quit")
	--menu()
end

function love.draw()
	if(gamestate == "main_menu") then
		button_draw()
	end

	if(gamestate == "menu") then
		--  nothing yet
	end
end

function love.update()
	-- body
	if(gamestate == "menu") then
		-- menu before you start playing and before you connect
		menu()
	end
	if(gamestate == "main_menu") then
	end

end

function love.mousepressed(x,y)
	if(gamestate== "main_menu") then
		button_click(x,y)
	end
end