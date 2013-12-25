import pygame
from pygame.locals import *
from time import sleep
import serial



class App:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("Joystick Analyzer")

        # Set up the joystick
        pygame.joystick.init()

        self.my_joystick = None
        self.joystick_names = []

        # Enumerate joysticks
        for i in range(0, pygame.joystick.get_count()):
            self.joystick_names.append(pygame.joystick.Joystick(i).get_name())

        print self.joystick_names

        # By default, load the first available joystick.
        if (len(self.joystick_names) > 0):
            self.my_joystick = pygame.joystick.Joystick(0)
            self.my_joystick.init()

        max_joy = max(self.my_joystick.get_numaxes(),
                      self.my_joystick.get_numbuttons(),
                      self.my_joystick.get_numhats())

        self.screen = pygame.display.set_mode( (max_joy * 30 + 10, 170) )

        self.font = pygame.font.SysFont("Courier", 20)

    # A couple of joystick functions...
    def check_axis(self, p_axis):
        if (self.my_joystick):
            if (p_axis < self.my_joystick.get_numaxes()):
                return self.my_joystick.get_axis(p_axis)

        return 0

    def check_button(self, p_button):
        if (self.my_joystick):
            if (p_button < self.my_joystick.get_numbuttons()):
                return self.my_joystick.get_button(p_button)

        return False

    def check_hat(self, p_hat):
        if (self.my_joystick):
            if (p_hat < self.my_joystick.get_numhats()):
                return self.my_joystick.get_hat(p_hat)

        return (0, 0)

    def draw_text(self, text, x, y, color, align_right=False):
        surface = self.font.render(text, True, color, (0, 0, 0))
        surface.set_colorkey( (0, 0, 0) )

        self.screen.blit(surface, (x, y))

    def center_text(self, text, x, y, color):
        surface = self.font.render(text, True, color, (0, 0, 0))
        surface.set_colorkey( (0, 0, 0) )

        self.screen.blit(surface, (x - surface.get_width() / 2,
                                   y - surface.get_height() / 2))

    def main(self):
        print s

        while (True):
            self.g_keys = pygame.event.get()

            self.screen.fill(0)

            for event in self.g_keys:
                if (event.type == KEYDOWN and event.key == K_ESCAPE):
                    self.quit()
                    return

                elif (event.type == QUIT):
                    self.quit()
                    return

            self.draw_text("Joystick Name:  %s" % self.joystick_names[0],
                           5, 5, (0, 255, 0))

            #self.draw_text("Axes (%d)" % self.my_joystick.get_numaxes(),
            #               5, 25, (255, 255, 255))


            # left
            la = int(round(self.my_joystick.get_axis(0) * 100))
            self.draw_text("Left (%f)" % self.my_joystick.get_axis(0),
                           5, 25, (255, 255, 255))
            lh = int(round(self.my_joystick.get_axis(1) * 100))
            self.draw_text("(%f)" % self.my_joystick.get_axis(1),
                           200, 25, (255, 255, 255))


            # right
            ra = int(round(self.my_joystick.get_axis(2) * 100))
            self.draw_text("Right (%f)" % self.my_joystick.get_axis(2),
                           5, 50, (255, 255, 255))
            rh = int(round(self.my_joystick.get_axis(3) * 100))
            self.draw_text("(%f)" % self.my_joystick.get_axis(3),
                           200, 50, (255, 255, 255))

            #print la + ',' + lh + ',' + ra + ',' + rh

            print '{0},{1},{2},{3}-'.format(la,lh,ra,rh)
            s.write('{0},{1},{2},{3}-'.format(la,lh,ra,rh))
            pygame.display.flip()

            sleep(0.1)

    def quit(self):
        pygame.display.quit()

s = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

app = App()
app.main()
