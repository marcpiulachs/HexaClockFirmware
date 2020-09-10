#!/usr/bin/python3
import pygame
import datetime
import random
import math

class ColorTools:
	def __init__(self):
		pass
	
	@staticmethod
	def hsv_to_rgb(h,s,v):
		if (s == 0):
			return (v,v,v)

		region = h // 43
		remainder = int( (h - (region * 43)) * 6 )

		p = (v * (255 - s)) >> 8;
		q = (v * (255 - ((s * remainder) >> 8))) >> 8
		t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8

		if (region==0):
			return (v,t,p)
		elif (region==1):
			return (q,v,p)
		elif (region==2):
			return (p,v,t)
		elif (region==3):
			return (p,q,v)
		elif (region==4):
			return (t,p,v)
		else:
			return (v,p,q)
class Color:
	def __init__(self, R, G, B):
		self.R = R
		self.G = G
		self.B = B

	def fade(self, x):
		self.R = max(min(self.R+x,255),0)
		self.G = max(min(self.G+x,255),0)
		self.B = max(min(self.B+x,255),0)

	@property
	def is_black(self):
		return self.R == 0 and self.G == 0 and self.B == 0	

	@property
	def pcol(self):
		return (self.R,self.G,self.B)

class StartAnimator(object):
		STATE_START = 0
		STATE_WIFI = 1
		STATE_WIFI_SETUP = 2

		def __init__(self,):
			super(StartAnimator, self).__init__()
			self.circles = [
				[95,96,92,91,89,90,78,77,76,61,60,45,44,29,28,13,14,12,11,3,4,2,1,5,6,8,7,19,20,21,36,37,52,53,68,69,84,83,85,86,94,93],
				[87,88,80,79,74,75,62,59,46,43,30,27,26,15,16,10,9,17,18,23,22,35,38,51,54,67,70,71,82,81],
				[72,73,64,63,58,47,42,32,31,25,24,33,34,39,50,55,66,65],
				[56,57,48,41,40,49],
			]
			self.wifi = [
				69,84,83,85,86,94,93,95,96,92,91,89,90,78,77,76,
				38,51,54,55,66,65,72,73,64,63,58,59,46,43,
				24,25
			]

			self.step = 0
			self.state = 0

		def run(self):
			buff = [Color(0,0,0)]*96

			if self.state == self.STATE_START:
				for digit in self.circles[min(self.step%16//4,3)]:
					buff[digit-1] = Color(255,255,255)
				self.step += 1

			elif self.state == self.STATE_WIFI:
				c = 10*(self.step % 25)
				if(c>125):
					c=255-c
				if self.step % 25 <12:
					for digit in self.wifi:
						buff[digit-1] = Color(c,c,c)
				else:
					for digit in self.wifi:
						buff[digit-1] = Color(c,c,c)
				self.step += 1

			elif self.state == self.STATE_WIFI_SETUP:
				for digit in self.wifi:
					buff[digit-1] = Color(50,50,255)
			return buff
class ColorRollAnimation(object):
		def __init__(self):
			super(ColorRollAnimation, self).__init__()
			self.hue = 0.0
			self.speed = 100

		def run(self):
			self.hue += self.speed/100
			if (self.hue>255):
				self.hue=0
			r,g,b = ColorTools.hsv_to_rgb(self.hue,255,255)
			return [Color(int(r),int(g),int(b))]*96

		def set_speed(self,speed):
			self.speed = speed

		def hsv_to_rgb(self,h,s,v):

				if (s == 0):
					return (v,v,v)

				region = h // 43
				remainder = int( (h - (region * 43)) * 6 )

				p = (v * (255 - s)) >> 8;
				q = (v * (255 - ((s * remainder) >> 8))) >> 8
				t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8

				if (region==0):
					return (v,t,p)
				elif (region==1):
					return (q,v,p)
				elif (region==2):
					return (p,v,t)
				elif (region==3):
					return (p,q,v)
				elif (region==4):
					return (t,p,v)
				else:
					return (v,p,q)
class BreathingColorAnnimation(object):
		def __init__(self,hue=50,strenght=180, inverted=False):
			super(BreathingColorAnnimation, self).__init__()
			self.circles = [
				[56,57,48,41,40,49],
				[72,73,64,63,58,47,42,61,32,31,25,24,33,34,39,50,55,66,65],
				[87,88,80,79,74,75,62,59,46,43,30,27,26,15,16,10,9,17,18,23,22,35,38,51,54,67,70,71,82,81],
				[95,96,92,91,89,90,78,77,76,61,60,45,44,29,28,13,14,12,11,3,4,2,1,5,6,8,7,19,20,21,36,37,52,53,68,69,84,83,85,86,94,93]
			]
			self.circles_lumi_offset = [120,140,150,160]
			self.circles_lumi_orientation = -1
			self.hue = hue
			self.luminace = 255
			self.speed = 100
			self.inverted = inverted
			self.strenght = strenght

		def run(self):
			for i in range(len(self.circles_lumi_offset)-1):
				self.circles_lumi_offset[i+1] = self.circles_lumi_offset[i] + 20

			self.circles_lumi_offset[0]+= self.speed//10 * self.circles_lumi_orientation
			if(self.circles_lumi_offset[0]>215 or self.circles_lumi_offset[0]<(255-self.strenght)):
				self.circles_lumi_orientation*=-1

			buff = [Color(0,0,0)]*96
			for i in range(len(self.circles)):
				m = self.circles_lumi_offset[i] if not self.inverted else 255-self.circles_lumi_offset[i]
				r,g,b = ColorTools.hsv_to_rgb(self.hue,255,m)
				r = 255 if r>255 else (0 if r<0 else r)
				g = 255 if g>255 else (0 if g<0 else g)
				b = 255 if b>255 else (0 if b<0 else b)
				c= Color(int(r),int(g),int(b))
				for digit in self.circles[i]:
					buff[digit-1] = c

			return buff

		def set_speed(self,speed):
			self.speed = speed
class ChristmasAnnimation(object):
		def __init__(self,
			flake_colors=Color(255,0,100),
			bg_color=Color(200,0,20)
			):
			super(ChristmasAnnimation, self).__init__()
			self.grass = [21,20,18,19,17,16,14,15,13,28,7,8,9,10,11,12,6,5,4,3,2,1]
			self.point_matrix = [
				[0 ,0 ,0 ,95,96,0 ,0 ,0 ],
				[0 ,0 ,94,93,92,91,0 ,0 ],
				[0 ,85,96,87,88,89,90,0 ],
				[84,83,82,81,80,79,78,77],
				[69,70,71,72,73,74,75,76],
				[68,67,66,65,64,63,62,61],
				[53,54,55,56,57,58,59,60],
				[52,51,50,49,48,47,46,45],
				[37,38,39,40,41,42,43,44],
				[36,35,34,33,32,31,30,29],
				[21,22,23,24,25,26,27,28],
				[20,19,18,17,16,15,14,13],
				[0 ,7 ,8 ,9 ,10,11,12,0 ],
				[0 ,0 ,6 ,5 ,4 ,3 ,0 ,0 ],
				[0 ,0 ,0 ,1 ,2 ,0 ,0 ,0 ]
			]
			self.snowflake_matrix = [
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
				[0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ],
			]
			self.flake_colors=flake_colors
			self.bg_color=bg_color
			self.snowflake_count = 0
			self.s = 0
			self.speed = 100

		def spawn_flakes(self):
			x = random.randint(0,7)
			y = 0
			while self.point_matrix[y][x] == 0:
				y+=1
			if self.snowflake_matrix[y][x] ==1:
				self.spawn_flakes()
			else:
				self.snowflake_matrix[y][x] = 1
				self.snowflake_count+=1

		def fall_flakes(self):
			for y in range(12,0,-1):
				for x in range(0,8):
					if self.snowflake_matrix[y-1][x] == 1:
						self.snowflake_matrix[y-1][x] = 0
						if y != 12:
							self.snowflake_matrix[y][x] = 1
						else:
							self.snowflake_count-=1

		def run(self):
			buff = [self.bg_color]*96

			for digit in self.grass:
				buff[digit-1] = Color(0,150,0)

			while (self.snowflake_count<4):
				self.spawn_flakes()
			
			if self.s>100:
				self.fall_flakes()
				self.s = 0

			self.s += self.speed

			for y in range(0,12):
				for x in range(0,8):
					buff[self.point_matrix[y][x]-1] = self.flake_colors if self.snowflake_matrix[y][x] == 1 else self.bg_color

			return buff

		def set_speed(self,speed):
			self.speed = speed
class ScrollingAnnimation(object):
		def __init__(self, color=Color(255,0,0),accent_color='g',orientation=True):
			super(ScrollingAnnimation, self).__init__()
			self.stepper = 0
			self.speed = 100
			self.luminance_buffer = [0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14, 16, 17, 18, 20, 21, 22, 24, 25, 26, 28, 29, 30, 32, 33, 34, 36, 37, 38, 40, 41, 42, 44, 45, 46, 48, 49, 50, 52, 53, 54, 56, 57, 58, 60, 61, 62, 64, 65, 66, 68, 69, 70, 72, 73, 74, 76, 77, 78, 80, 81, 82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96, 97, 98, 100, 101, 102, 104, 105, 106, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120, 121, 122, 124, 125, 127, 127, 125, 124, 122, 121, 120, 118, 117, 116, 114, 113, 112, 110, 109, 108, 106, 105, 104, 102, 101, 100, 98, 97, 96, 94, 93, 92, 90, 89, 88, 86, 85, 84, 82, 81, 80, 78, 77, 76, 74, 73, 72, 70, 69, 68, 66, 65, 64, 62, 61, 60, 58, 57, 56, 54, 53, 52, 50, 49, 48, 46, 45, 44, 42, 41, 40, 38, 37, 36, 34, 33, 32, 30, 29, 28, 26, 25, 24, 22, 21, 20, 18, 17, 16, 14, 13, 12, 10, 9, 8, 6, 5, 4, 2, 1, 0]
			self.orientation = orientation
			self.accent_color = accent_color
			self.color=color

		def run(self):
			buff = [Color(0,0,0)]*96

			while self.stepper>100:
				if self.orientation:
					#int tampon = tab[0];
					#for (int i = 1; i < size; ++i){
					#	tab[i - 1] = tab[i];
					#}
					#tab[size - 1] = tampon;
					b = self.luminance_buffer[0]
					for i in list(range(1,96+96)): 
						self.luminance_buffer[i-1] = self.luminance_buffer[i]
					self.luminance_buffer[96+95] = b
				else:
					self.luminance_buffer[0] = self.luminance_buffer[96+95]
					for i in list(range(96+96))[:0:-1] : 
						self.luminance_buffer[i] = self.luminance_buffer[(i-1)]

				self.stepper -=100
			self.stepper += self.speed

			for i in range(96):
				if(self.accent_color=='r'):
					buff[i] = Color(min(self.color.R + self.luminance_buffer[i],255),self.color.G,self.color.B)
				if(self.accent_color=='g'):
					buff[i] = Color(self.color.R, min(self.color.G + self.luminance_buffer[i],255),self.color.B)
				if(self.accent_color=='b'):
					buff[i] = Color(self.color.R,self.color.G,min(self.color.B + self.luminance_buffer[i],255))

			return buff

		def set_speed(self,speed):
			self.speed = speed
class FishAnnimation(object):
		def __init__(self,orientation=True, color=Color(255,0,0),accent_color='r'):
			super(FishAnnimation, self).__init__()
			self.accent_color = accent_color
			self.color=color

			self.stepper = 0
			self.speed = 100
			self.luminance_buffer = [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 127, 127, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25]
			self.orientation = orientation
			self.fish_matrix = [
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
			]

		def run(self):
			buff = [Color(0,0,0)]*96

			if self.stepper>300:
				for a in range(3):
					self.luminance_buffer[0] = self.luminance_buffer[96+95]
					for i in list(range(96+96))[:0:-1] : 
						self.luminance_buffer[i] = self.luminance_buffer[(i-1)]
				self.fish_matrix[random.randint(0,95)] = 255
				self.stepper = 0

				for b in range(96):
					if self.fish_matrix[b]:
						self.fish_matrix[b] = max(self.fish_matrix[b] - self.speed//10 , 0)

			for i in range(96):
				if(self.accent_color=='r'):
					buff[i] = Color(min(self.color.R + self.luminance_buffer[i],255),self.color.G,self.color.B)
				if(self.accent_color=='g'):
					buff[i] = Color(self.color.R, min(self.color.G + self.luminance_buffer[i],255),self.color.B)
				if(self.accent_color=='b'):
					buff[i] = Color(self.color.R,self.color.G,min(self.color.B + self.luminance_buffer[i],255))

				c = min(5 + self.luminance_buffer[i],255)  *  self.fish_matrix[i]  //255
				if self.fish_matrix[i]:
					if(self.accent_color=='r'):
						buff[i] = Color(int(min(5 + self.luminance_buffer[i] *2.5 ,255)),c,c)
					if(self.accent_color=='g'):
						buff[i] = Color(c,int(min(5 + self.luminance_buffer[i] *2.5 ,255)),c)
					if(self.accent_color=='b'):
						buff[i] = Color(c,c,  int(min(5 + self.luminance_buffer[i] *2.5 ,255)))
					


			self.stepper += self.speed

			return buff

		def set_speed(self,speed):
			self.speed = speed


class SimulatorScreen(object):
	def __init__(self,display_numbers=False):
		super(SimulatorScreen, self).__init__()
		self.LedMapPyGame = [
			34,49,
			21,35,50,64,
			10,22,36,51,65,77,
			1 ,11,23,37,52,66,78,88,
			2 ,12,24,38,53,67,79,89,
			3 ,13,25,39,54,68,80,90,
			4 ,14,26,40,55,69,81,91,
			5 ,15,27,41,56,70,82,92,
			6 ,16,28,42,57,71,83,93,
			7 ,17,29,43,58,72,84,94,
			8 ,18,30,44,59,73,85,95,
			9 ,19,31,45,60,74,86,96,
			20,32,46,61,75,87,
			33,47,62,76,
			48,63
		]
		self.LedMapMatrix = [
			95,96,
			94,93,92,91,
			85,86,87,88,89,90,
			84,83,82,81,80,79,78,77,
			69,70,71,72,73,74,75,76,
			68,67,66,65,64,63,62,61,
			53,54,55,56,57,58,59,60,
			52,51,50,49,48,47,46,45,
			37,38,39,40,41,42,43,44,
			36,35,34,33,32,31,30,29,
			21,22,23,24,25,26,27,28,
			20,19,18,17,16,15,14,13,
			7,8,9,10,11,12,
			6,5,4,3,
			1,2
		]
		pygame.init()
		self.size = (700, 700)
		self.screen = pygame.display.set_mode(self.size) 
		self.display_numbers=display_numbers
		pygame.display.set_caption("Simulator")
	
	def text(self,txt,X,Y):
		font = pygame.font.Font('freesansbold.ttf', 16) 
		text = font.render(txt, True, (0, 0, 0), (255,255,255)) 
		textRect = text.get_rect()  
		textRect.center = (X, Y) 
		self.screen.blit(text, textRect) 

	def update(self,led_buf):
		self.screen.fill((0, 0, 0))
		s = 40
		c = 0
		trigA = True
		inv = [1,1,1,1,0,1,1,1]
		yl=[8,10,12,14,14,12,10,8]
		for i in range(-4,4):
			if inv[i+4]:
				trigA = not trigA
			xp=i+4
			for yp in range(yl[xp]+1):
				x=xp*s + int(s*i//1.75)
				y=yp*s - s* yl[xp]//2
				y+=350
				x+=350 - int(3.5*s)
				c+=1
				COLOR = led_buf[self.LedMapMatrix[self.LedMapPyGame.index(c)] -1 ]
				if trigA:
					pygame.draw.polygon(self.screen,COLOR.pcol,[
						(x-22,y+30),
						(x+22,y),
						(x-22,y-30)
					])
				else:
					pygame.draw.polygon(self.screen,COLOR.pcol,[
						(x+22,y+30),
						(x-22,y),
						(x+22,y-30)
					])
				trigA = not trigA

				if self.display_numbers:
					self.text(
						str(self.LedMapMatrix[self.LedMapPyGame.index(c)]),
						x,y
					)

		pygame.display.flip()
def generate_clock():
	font_position = [
		[93,92,85,86,81,80,70,71,65,64],
		[91,90,87,88,79,78,72,73,63,62],
		[33,32,22,23,17,16,7,8,5,4],
		[31,30,24,25,15,14,9,10,3,2],
	]

	font = [
		0B1111001111000000,
		0B0101010101000000,
		0B1101111011000000,
		0B1101110111000000,
		0B0011110101000000,
		0B1110110111000000,
		0B1110111111000000,
		0B1111010101000000,
		0B1111111111000000,
		0B1111110111000000 
	]

	buf = [Color(0,0,0)]*96

	now = datetime.datetime.now()
	hour = now.hour
	minutes = now.minute

	digitHour0 = font[hour//10]
	digitHour1 = font[hour%10]
	digitMinutes0 = font[minutes//10]
	digitMinutes1 = font[minutes%10]

	for i in range(10):
		if((digitHour0 >> (15-i)) & 0x01):
			buf[ font_position[0][i] ] = Color(255,255,255);

		if((digitHour1 >> (15-i)) & 0x01):
			buf[ font_position[1][i] ] = Color(255,255,255);


		if((digitMinutes0 >> (15-i)) & 0x01):
			buf[ font_position[2][i] ] = Color(255,255,255);

		if((digitMinutes1 >> (15-i)) & 0x01):
			buf[ font_position[3][i] ] = Color(255,255,255);
	
	return buf			
def merge_buf(a,b): 
	out = [Color(0,0,0)]*96
	for i in range(len(a)):
		if b[i].is_black:
			out[i] = a[i]
		else:
			out[i] = b[i]
	return out

ANNIMATION_BUFFER = [Color(225,70,20)]*96

start_annimation = StartAnimator()

annimation = ColorRollAnimation()
annimation.set_speed(10)
annimation = BreathingColorAnnimation(hue=220,strenght=180,inverted=False)
annimation.set_speed(10)
annimation = ChristmasAnnimation()
annimation.set_speed(10)
annimation = ScrollingAnnimation(orientation=False,color=Color(10,0,0), accent_color='b')
annimation.set_speed(100)
annimation = FishAnnimation(color=Color(255,0,0), accent_color='r')
annimation.set_speed(100)

done=False
clock = pygame.time.Clock()
screen = SimulatorScreen(display_numbers=False)
#for y in range(500):
#	screen.update(start_annimation.run())
#	clock.tick(60)
#	if y>50:
#		start_annimation.state = StartAnimator.STATE_WIFI
#	if y>200:
#		start_annimation.state = StartAnimator.STATE_WIFI_SETUP


while not done:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			done = True

	ANNIMATION_BUFFER = annimation.run()

	screen.update(merge_buf(ANNIMATION_BUFFER,generate_clock()))
	#screen.update(ANNIMATION_BUFFER)
	clock.tick(60)
 
# Close the window and quit.
pygame.quit()