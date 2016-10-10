HC = require 'libs/HC'

function love.load()
	love.graphics.setBackgroundColor( 50, 50, 50 )
	Collider = HC(100, on_collide) -- Crea una nueva colision

	-- cuadros de colision de la bola y los jugadores
	ball = Collider:addCircle(400,300, 10)
    p1   = Collider:addRectangle(10,250, 20,100)
    p2   = Collider:addRectangle(770,250, 20,100)
 	p3   = Collider:addRectangle(360, 10, 100, 20)
 	p4   = Collider:addRectangle(360,570, 100, 20)
    -- borderas que permiten determinar ganador
    goalTop    = Collider:addRectangle(0,-100, 800,100)
    goalBottom = Collider:addRectangle(0,600, 800,100)
    goalLeft   = Collider:addRectangle(-100,0, 100,600)
    goalRight  = Collider:addRectangle(800,0, 100,600)

    ball.velocity = {x = -100, y = 0}
end

-- funcion que maneja la colision de los objetos
function on_collide(dt, shape_a, shape_b)
	-- Primero identificamos que parametro de entrada es la bola y cual es un jugador
	local other
	if shape_a == ball then
		other = shape_b
	elseif shape_b == ball then
		other = shape_a
	else
		return
	end

	if other == goalLeft then
		ball.velocity = {x = 100, y = 0}
		ball:moveTo(400,300)
	elseif other == goalRight then
		ball.velocity = {x= -100, y = 0}
		ball:moveTo(400,300)
	elseif other == goalTop then
		ball.velocity = {x= 0, y = 100}
		ball:moveTo(400,300)
	elseif other == goalBottom then
		ball.velocity = {x= 0, y = -100}
		ball:moveTo(400,300)
		--ball.velocity.y = -ball.velocity.y
	else
		-- lo siguiente permite que la bola rebote al tocar la barra de un jugador
		local px, py = other:center()
		local bx, by = ball:center()

		if other == p1 or other == p2 then
			local dy = by - py
			ball.velocity.x = -ball.velocity.x
			ball.velocity.y = dy
			-- lo siguiente permite mantener la bola con velocidad constante
			local len = math.sqrt(ball.velocity.x^2 + ball.velocity.y^2)
			ball.velocity.x = ball.velocity.x / len * 100
			ball.velocity.y = ball.velocity.y / len * 100
		else
			local dx = bx - px
			ball.velocity.x = dx
			ball.velocity.y = -ball.velocity.y
			-- lo siguiente permite mantener la bola con velocidad constante
			local len = math.sqrt(ball.velocity.x^2 + ball.velocity.y^2)
			ball.velocity.x = ball.velocity.x / len * 100
			ball.velocity.y = ball.velocity.y / len * 100
		end
	end
end

function love.update(dt)
	Collider:update(dt) -- Verifica si hay colision en todo momento

	ball:move(ball.velocity.x * dt, ball.velocity.y * dt)

	-- Controles p1
	if love.keyboard.isDown('q') then
		p1:move(0,-100 * dt)
	elseif love.keyboard.isDown('w') then
		p1:move(0, 100 * dt)
	end
	-- Controles p2
	elseif love.keyboard.isDown('a') then 
		p2:move(0,-100 * dt)
	elseif love.keyboard.isDown('s') then
		p2:move(0, 100 * dt)
	end
	-- Controles p3
	if love.keyboard.isDown('z') then 
		p3:move(-100 * dt, 0)
	elseif love.keyboard.isDown('x') then
		p3:move(100 * dt, 0)
	end
	-- Controles p4
	if love.keyboard.isDown('c') then 
		p4:move(-100 * dt, 0)
	elseif love.keyboard.isDown('v') then
		p4:move( 100 * dt, 0)
	end

end

function love.draw()
	ball:draw('fill',9)
	p1:draw('fill')
	p2:draw('fill')
	p3:draw('fill')
	p4:draw('fill')

end