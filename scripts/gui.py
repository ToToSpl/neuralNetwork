import pygame

RESOLUTION = 28
WINSIZE = 336
PIXELSIZE = WINSIZE/RESOLUTION
DOWNBAR = 100

pointArr = [[0 for i in range(RESOLUTION)] for j in range(RESOLUTION)]

isGuessed = False
guessedNum = -1

def text_objects(text, font, clr):
    textSurface = font.render(text, True, clr)
    return textSurface, textSurface.get_rect()

class Button:
    pos = (0,0)
    size = (0,0)
    color = (0,0,0)
    text = ''
    def __init__(self,pos,size,color,text):
        self.pos = pos
        self.size = size
        self.color = color
        self.text = text
    
    def draw(self):
        pygame.draw.rect(screen,self.color,
        (self.pos[0],self.pos[1],self.size[0],self.size[1]),0)

        largeText = pygame.font.Font('freesansbold.ttf',16)
        TextSurf, TextRect = text_objects(self.text, largeText, (0,0,0))
        TextRect.center = (self.pos[0]+self.size[0]/2,self.pos[1]+self.size[1]/2)
        screen.blit(TextSurf, TextRect)

    def update(self):
        x,y = pygame.mouse.get_pos()
        if self.pos[0] <= x <= self.pos[0]+self.size[0] and self.pos[1] <= y <= self.pos[1]+self.size[1]:
            return True
        else:
            return False


clear = Button((WINSIZE/2-100,WINSIZE+DOWNBAR/2-20),(75,30),(255,0,0),'CLEAR')
guess = Button((WINSIZE/2+25,WINSIZE+DOWNBAR/2-20),(75,30),(0,255,0),'GUESS')

def main():
     
    pygame.init()
    global screen
    screen = pygame.display.set_mode((WINSIZE,WINSIZE+DOWNBAR))
    screen.set_alpha(None)
    pygame.event.set_allowed([pygame.QUIT, pygame.MOUSEBUTTONDOWN, pygame.MOUSEBUTTONUP])
    pygame.display.set_caption("Neural Network GUI")
    
    running = True
    drawing = False
     
    while running:
        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN:
                drawing = True
            elif event.type == pygame.MOUSEBUTTONUP:
                drawing = False
            elif event.type == pygame.QUIT:
                running = False

        if drawing:
            draw()
        update()

def update():
    screen.fill((0, 0, 0))
    clear.draw()
    guess.draw()
    #drawGrid()

    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if pointArr[i][j] == 1:
                pygame.draw.rect(screen,(200,200,200),
                (i*PIXELSIZE,j*PIXELSIZE,PIXELSIZE,PIXELSIZE),0)

    if isGuessed:
        text = 'Is this ' + str(guessedNum) + '?'
        largeText = pygame.font.Font('freesansbold.ttf',16)
        TextSurf, TextRect = text_objects(text, largeText, (255,255,255))
        TextRect.center = (WINSIZE/2,WINSIZE+DOWNBAR-16)
        screen.blit(TextSurf, TextRect)

    pygame.draw.line(screen,(200,200,200),(0,WINSIZE),(WINSIZE,WINSIZE))
    pygame.display.flip()


def draw():
    global isGuessed,guessedNum
    pos = (pygame.mouse.get_pos())
    if pos[1] <= WINSIZE and pos[0] <= WINSIZE:
        x=pos[0]
        y=pos[1]
        pointArr[int(x/PIXELSIZE)][int(y/PIXELSIZE)] = 1
    

    if clear.update():
        isGuessed = False
        for i in range(RESOLUTION):
            for j in range(RESOLUTION):
                pointArr[i][j]=0

    if guess.update():
        isGuessed = True
        guessedNum = guessNumber()


def drawGrid():
    for i in range(RESOLUTION):
        pygame.draw.line(screen,(200,200,200),(i*PIXELSIZE,0),(i*PIXELSIZE,WINSIZE))
    
    for i in range(RESOLUTION):
        pygame.draw.line(screen,(200,200,200),(0,i*PIXELSIZE),(WINSIZE,i*PIXELSIZE))

def guessNumber():
    return -1

if __name__=="__main__":
    main()