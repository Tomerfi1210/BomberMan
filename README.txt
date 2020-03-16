Title: Bomberman Final Project

Student 1:

Name: Tomer Fisher (תומר פישר)

ID:205364151

Student 2:

Name: Shahar Aviv (שחר אביב)

ID:203489307


General Description:

This program is a bomberman clone

objects include:

*Wall

*Bomb

*Door

*Robot

*Guards

*Menu

*Board

*Rock




Classes
----Controller:
	controller is in charge of the whole game
	holds guards, staticObjects, bombs, gifts, robot
		
----Menu:
	Menu is in charge of the menu that holds the Start and Exit button
		
			
		
----Board:
	Board holds the map
		
----Object:
	Abstract class for a game objects
		
	----UnMoveAble:
		Abstarct class for static objects
		like wall,door, rock
			
		----Wall:
			inherits from UnMoveAble
				
		----Rock:
			inherits from UnMoveAble

		----Door:
			inherits from UnMoveAble
		
	----MoveAble:
		Abstarct class for dynamic objects
		like robot and guards
			
		----Guards:
			Abstarct class 
				
			----SmartGuard:
				inherits from Guards, this guard has an algorithm for chasing robot
					
			----StupidGuard:
				inherits from Guards, this guard has random movement
					
		----Robot:
			class holds robot with his movement
			
		
		
----Pictures:
	Singleton holds textures
		


List Of Files:

.h files
	Board
	Bomb
	BombGift
	Command
	Controller
	GameObjects
	Gifts
	Guards
	Menu
	Pictures
	Robot
	etc
	
	
.cpp Files:
	Controller
	Board
	wall
	Guards
	Robot
	SmartGuard
	StupidGurd
	main
	Pictures
	Rock
	StartingMenu
	etc

Main design patterns and data stracture:
	vector of staticObjects*
	vector of guards*
	vector of bombs*
	vector of gifts*
	command
	singelton
	unickptr
	map
	factory
	double dispatch

Worthy To Mention Algorithms:
	Algorithm for moving smart guards

Known bugs :
	the guards are bit shacking (winter time issues)

Other Notes:
	By pressing on SPACE button your dropping a bomb with the robot
	The gifts are hide under some rocks 