-- table players
players = {}
balls = {}

playersBackup = {}
ballsBackup = {}

port = 18025
portBackup = 9090

function load( ip,name, ipB )
	-- Collider = HC( 100, on_collision )
	-- set grey background
	love.graphics.setBackgroundColor( 50, 50, 50 )

	client = lube.client()
	client:setHandshake("lets play pong!")
	client:setCallback(ClientReceive)
	client:connect(ip, port) -- 82.24.82.156 marks
    client:send("name" .. name)
    
    client:setPing(true, 3, "you there?\n")
	holding = false
end

function ClientReceive(data)
	players = TSerial.unpack( data )
	local clientstatus = data:gfind("Client=(.*)")()
	if clientstatus == "inHold" then
		draw_connectionrejected()
	else
		holding = false
	end
	if data == 'changeServer' then
		print("it worked?")
		client:connect(ip, portBackup) -- 82.24.82.156 marks
	end



end

function draw_connectionrejected()
	love.graphics.draw("Connection rejected by server, server might be full", 20, 20)
end

function love.draw()

	for k, v in pairs(players) do
		if (v.id == "p1" or v.id == "p2") and not holding then
			love.graphics.rectangle('fill', v.x-10, v.y-50, 20, 100)
			love.graphics.print(v.name, v.x-10, v.y-80)
			love.graphics.print(v.points, v.x-10, v.y+70)
		else
			if(not holding) then
				if (v.id == "p4") then
					love.graphics.rectangle('fill', v.x-50, v.y-10, 100, 20)
					love.graphics.print(v.name, v.x-10, v.y-40)
					love.graphics.print(v.points, v.x-80, v.y-10)
				else 
					love.graphics.rectangle('fill', v.x-50, v.y-10, 100, 20)
					love.graphics.print(v.name, v.x-10, v.y+10)
					love.graphics.print(v.points, v.x-80, v.y-10)
				end
			else
				draw_connectionrejected()
			end
		end

		love.graphics.circle('fill', v.balls.x, v.balls.y, v.balls.r)
	end

	-- debug
	drawMessages()
	-- fps display
	love.graphics.print( love.timer.getFPS(), 10, 10 )
end


function love.update( dt )
	-- Collider:update( dt )
	client:update(dt)
	client:doPing(dt)

	-- Controles
	if love.keyboard.isDown('q')  then
		client:send('q')
	elseif love.keyboard.isDown('w') then
		client:send('w')
	end
end

function love.keypressed( key )

end

function love.keyreleased( key )
end

function love.mousepressed( x, y, key )
end

function love.quit()
	print("Me desconecte!")
	client:send('quit')
end