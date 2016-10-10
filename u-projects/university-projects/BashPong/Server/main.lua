require 'libs/console'
require 'libs/math'

require 'libs/LUBE'
require 'libs/TSerial'
require 'socket'

HC = require 'libs/HC'

players = {}
player_paddles = {}
balls = {}
port = 18025
portBackup = 9090
localhost = "127.0.0.1"

function love.load()
	Collider = HC( 100, on_collide )
	love.graphics.setBackgroundColor( 50, 50, 50 )

	clientsConnected = 0
	player_one = 0
	player_two = 0
	player_three = 0
	player_four = 0
    
    --newSocket = socket.udp()
    --newSocket.setpeername(localhost,portBackup)
    
    player_one_id = 0
    player_two_id = 0
    player_three_id = 0
    player_four_id = 0
    
	server = lube.server(port)
	server:setCallback(ServerReceive, ServerConnect, ServerDisconnect)
	server:setHandshake("lets play pong!")
    server:setPing(true, 9, "you there?\n")
    
    goalTop    = Collider:addRectangle(0,-100, 800,100)
    goalBottom = Collider:addRectangle(0,600, 800,100)
    goalLeft   = Collider:addRectangle(-100,0, 100,600)
    goalRight  = Collider:addRectangle(800,0, 100,600)

    gamestate = false
end
-- NETWORKING --

function ServerConnect(id, port)
	print("Server Connect")
	if clientsConnected < 4 then
		if player_one == 0 then
			print("P1: ", id)
            player_one_id = id
			player_paddles[id] = Collider:addRectangle(10,250,20,100)
			player_paddles[id].id = id
			players[id] = { x = 10, y = 200, name = "player1", id = "p1", points = 0,
			 balls = {x = 400, y = 300, r = 10, vx = -2, vy =0}}
            
			balls[id] = Collider:addCircle(400,300, 10)
			balls[id].velocity = {x = -2, y = 0}
			player_one = 1
		elseif player_two == 0 then
			print("P2: ", id)
            player_two_id = id
			player_paddles[id] = Collider:addRectangle(770,250, 20,100)
			player_paddles[id].id = id
			balls[id] = Collider:addCircle(400,300, 10)
			balls[id].velocity = {x = 2, y = 0}
			players[id] = { x = 770, y = 250, name = "player2", id = "p2", points = 0, 
			balls = {x = 400, y = 300, r = 10, vx = 2, vy =0}}
			
			player_two = 1
		elseif player_three == 0 then
			print("P3: ", id)
            player_three_id = id
			player_paddles[id] = Collider:addRectangle(350, 10, 100, 20)
			player_paddles[id].id = id
			balls[id] = Collider:addCircle(400,300, 10)
			balls[id].velocity = {x = 0, y = -2}
			players[id] = { x = 350, y = 10, name = "player3", id = "p3", points = 0, 
			balls = {x = 400, y = 300, r = 10, vx = 0, vy = -2}}
			
			player_three = 1
		elseif player_four == 0 then
			print("P4: ", id)
            player_four_id = id
			player_paddles[id] = Collider:addRectangle(350,570, 100, 20)
			player_paddles[id].id = id
			balls[id] = Collider:addCircle(400,300, 10)
			balls[id].velocity = {x = 0, y = 2}
			players[id] = { x = 350, y = 570, name = "player4", id = "p4", points = 0, 
			balls = {x = 400, y = 300, r = 10, vx = 0, vy =2}}
			
			player_four = 1
		else 
		end
	clientsConnected = clientsConnected + 1
	gamestate = true
	else
		server:send("inHold", ip)
	end
	
end

function ServerDisconnect(id)
	if (id == nil) then
		print("Disconnection!!")
	else
		if id > 0 then
			if(player_paddles[id].id == player_one_id) then
				print("Se libero p1")
				player_one = 0
			end
			if(player_paddles[id].id == player_two_id) then
				print("Se libero p2")
				player_two = 0
			end
			if(player_paddles[id].id == player_three_id) then
				print("Se libero p3")
				player_three = 0
			end
			if(player_paddles[id].id == player_four_id) then
				print("Se libero p4")
				player_four = 0
			end
	        Collider:remove(player_paddles[id])
			--player_paddles[id] = nil
	        Collider:remove(balls[id])
			--players[id] = nil
			table.remove(players, id)
			--balls[id] = nil
			clientsConnected = clientsConnected - 1
		end
	end
end

function ServerReceive(data, id)
	-- Actualiza el nombre
	if string.find(data, "name") then
		local player_name = string.sub(data, "5")
		players[id].name = player_name
	end

	local speed = 5
	--if players[id].name == "motz" then 
	--	speed = 10 end

	-- Controles p1
	if data == 'q' and player_one == 1 then
		if players[id].id == "p1" then
			player_paddles[id]:move(0,-speed)
		end
	end
	if data == 'w' and player_one == 1 then
		if players[id].id == "p1" then
			player_paddles[id]:move(0, speed)
		end
	end

	if data == 'q' and player_two == 1 then
		if players[id].id == "p2" then
			player_paddles[id]:move(0,-speed)
		end
	end
	if data == 'w' and player_two == 1 then
		if players[id].id == "p2" then
			player_paddles[id]:move(0, speed)
		end
	end

	if data == 'q' and player_three == 1 then
		if players[id].id == "p3" then 
			player_paddles[id]:move(-speed, 0)
		end
	end
	if data == 'w' and player_three == 1 then
		if players[id].id == "p3" then
			player_paddles[id]:move(speed, 0)
		end
	end

	if data == 'q' and player_four == 1 then
		if players[id].id == "p4" then 
			player_paddles[id]:move(-speed, 0)
		end
	end
	if data == 'w' and player_four == 1 then
		if players[id].id == "p4" then
			player_paddles[id]:move(speed, 0)
		end
	end

	if data == 'quit' then
		ServerDisconnect(id)
	end
end


-- COLLISION DETECTION --
-- funcion que maneja la colision de los objetos
function on_collide(dt, shape_a, shape_b)
	-- Primero identificamos que parametro de entrada es la bola y cual es un jugador
	local other, other2
	if shape_a == balls[player_one_id] or 
		shape_a == balls[player_two_id] or
		shape_a == balls[player_three_id] or
		shape_a == balls[player_four_id]  then
			other = shape_b -- Other indica el personaje o la pared
			other2 = shape_a -- other2 es la bola
	elseif shape_b == balls[player_one_id] or 
		shape_b == balls[player_two_id] or
		shape_b == balls[player_three_id] or
		shape_b == balls[player_four_id]  then
			other = shape_a -- Other indica el personaje o la pared
			other2 = shape_b
	else
		return
	end

	if other == goalLeft then
		if(player_one== 1) then
			other2.velocity = {x = 2, y = 0}
			other2:moveTo(400,300)
			players[player_one_id].points = players[player_one_id].points + 1
		else
			other2.velocity.x = -other2.velocity.x
		end
	elseif other == goalRight then
		if(player_two == 1) then
			other2.velocity = {x= -2, y = 0}
			other2:moveTo(400,300)
			players[player_two_id].points = players[player_two_id].points + 1
		else
			other2.velocity.x = -other2.velocity.x
		end
	elseif other == goalTop then
		if(player_three == 1) then
			other2.velocity = {x= 0, y = 2}
			other2:moveTo(400,300)
			players[player_three_id].points = players[player_three_id].points + 1
		else
			other2.velocity.y = -other2.velocity.y
		end
	elseif other == goalBottom then
		if(player_four == 1) then
			other2.velocity = {x= 0, y = -2}
			other2:moveTo(400,300)
			players[player_four_id].points = players[player_four_id].points + 1
		else
			other2.velocity.y = -other2.velocity.y
		end
	else
		-- lo siguiente permite que la bola rebote al tocar la barra de un jugador
		local px, py = other:center() -- paddle
		local bx, by = other2:center() -- ball
    
		if (other.id == player_one_id) or 
			(other.id == player_two_id) then
			local dy = (by - py)/20
			other2.velocity.x = -other2.velocity.x
			other2.velocity.y = dy
			-- lo siguiente permite mantener la bola con velocidad constante
			local len = math.sqrt(other2.velocity.x^2 + other2.velocity.y^2)
			other2.velocity.x = other2.velocity.x / len*2
			other2.velocity.y = other2.velocity.y / len*2
		end
		if(other.id == player_three_id) or (other.id == player_four_id) then
			local dx = (bx - px)/20
			other2.velocity.x = dx
			other2.velocity.y = -other2.velocity.y
			-- lo siguiente permite mantener la bola con velocidad constante
			local len = math.sqrt(other2.velocity.x^2 + other2.velocity.y^2)
			other2.velocity.x = other2.velocity.x / len*2
			other2.velocity.y = other2.velocity.y / len*2
		end
	end
end


function love.draw()
	drawMessages()
	
end

function love.update( dt)
	Collider:update( dt )
	server:update(dt)
	server:checkPing(dt)

	--ball:move(ball.velocity.x * dt, ball.velocity.y * dt)
	--balls[id]:move(players[id].balls.vx *dt, players[id].balls.vy * dt)
	for k, v in pairs( players ) do
		v.balls.vx = balls[k].velocity.x
		v.balls.vy = balls[k].velocity.y
		v.x, v.y = player_paddles[k]:center()
		v.balls.x,v.balls.y = balls[k]:center()
		balls[k]:move(v.balls.vx , v.balls.vy)	
	end

	server:send( TSerial.pack( players ) )

	if not (server) then
		print("Error, iniciando cambio de servidor")
		server = lube.server(portBackup)
	end


end

function love.keypressed( key )
end

function love.keyreleased( key )
end

function love.mousepressed( x, y, key )
end

function love.quit()
	print("Cambio de server?")
	server:send('changeServer')
end