button = {}
new_font = love.graphics.newFont(18)

-- Main menu, where the player can play, look up the highest score and exit
function button_spawn(x,y,text, id)
	table.insert(button, {x = x, y = y, text = text, id = id})
end

function button_draw()
	for i,v in ipairs(button) do
		love.graphics.setColor(255,255,255)
		love.graphics.setFont(new_font)
		love.graphics.print(v.text, v.x, v.y)
	end
end

function button_click(x,y)
	for i,v in ipairs(button) do
		if (x > v.x and x < v.x + new_font:getWidth(v.text)
			and y > v.y and y < v.y + new_font:getHeight()) then
			if(v.id == "quit") then
				love.event.push("quit")
			end
			if (v.id == "start") then
				gamestate = "menu"
			end
		end
	end	
end