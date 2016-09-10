--
-- ai.lua
-- basic AI for the computer player
--

MAP_NONE = 0
MAP_SOLID = 1

moveX = 0
moveY = 0
moveDelay = 0
bombDelay = 0
runAway = false

function main()
   posX, posY = aiGetPosition()
   width, height = aiGetMapSize()
   enemyX, enemyY = aiGetNearestPlayer()

   if moveDelay <= 0 then
      if enemyX ~= -1 then
	 moveX = enemyX
	 moveY = enemyY
	 moveDelay = 0.5
	 runAway = false
      end
      if aiIsDangerAt(posX, posY) then
	 distance = 1000
	 x = posX - 20
	 while x < posX + 20 do
	    y = posY - 20
	    while y < posY + 20 do
	       d = (posX - x) * (posX - x) + (posY - y) * (posY - y)
	       if x >= 0 and x < width and y >= 0 and y < height and d < distance and
	       (not aiIsDangerAt(x, y)) and aiMapGet(x, y) == MAP_NONE then
		  distance = d
		  moveX = x
		  moveY = y
		  runAway = true
		  moveDelay = 2.1
	       end
	       y = y + 1
	    end
	    x = x + 1
	 end
      end
   end

   if (not runAway) and aiGetBombs() > 0 then bombDelay = 0 end

   if enemyX ~= -1 and bombDelay <= 0 and aiGetBombs() > 0 then
      if aiDistanceTo(enemyX, enemyY) < 3.0 or
	 aiMapGet(posX + 1, posY) == MAP_SOLID or
	 aiMapGet(posX - 1, posY) == MAP_SOLID or
	 aiMapGet(posX, posY + 1) == MAP_SOLID or
         aiMapGet(posX, posY - 1) == MAP_SOLID then
	 bombDelay = 3.0
	 aiPlaceBomb()
      end
   end

   aiMoveTo(moveX, moveY, runAway)
end

function update(clock)
   moveDelay = moveDelay - clock
   bombDelay = bombDelay - clock
end
