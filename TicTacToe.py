'''
Simple Tic-Tac-Toe Game in Python
Written by Matthew D'Arcy
'''

from random import randint
from IPython.display import clear_output

p1_name = ''
p2_name = ''
p_turn = {'name': '', 'symbol': ''}
game_over = False
move_count = 0
spaces = {
    'm1': 1,
    'm2': 2,
    'm3': 3,
    'm4': 4,
    'm5': 5,
    'm6': 6,
    'm7': 7,
    'm8': 8,
    'm9': 9,
}


# Randomize player symbol and turn order

def rand(p1,p2):
    
    p1_first = randint(0,1)
    
    if p1_first == 0:
        
        return {'name': p2,'symbol':'O'}
    
    elif p1_first == 1:
        
        return {'name': p1,'symbol':'X'}


# Change turn between players

def swap_player():
    
    global p_turn
    
    global p1_name
    
    global p2_name
    
    if p_turn['symbol'] == 'X':
        
        p_turn = {'name': p2_name, 'symbol': 'O'}
        
    elif p_turn['symbol'] == 'O':
        
        p_turn = {'name': p1_name, 'symbol': 'X'}
    
    if game_over == False:
        clear_output()


# Welcome routine collecting user information

def welcome():
    
    print 'Welcome to tic-tac-tsssss!'
    
    print "Player 1, X's, please enter your name:"
    
    global p1_name
    
    p1_name = raw_input()
    
    print 'Welcome to tic-tac-tsssss, {x}'.format(x = p1_name)
    
    print 
    
    global p2_name
    
    print "Player 2, O's, please enter your name:"
    
    p2_name = raw_input()
    
    print 'Welcome to tic-tac-tsssss, {x}'.format(x = p2_name)
    
    print
    
    print 'Randomizing first player...'
    
    print
    
    global p_turn
    
    p_turn = rand(p1_name, p2_name)


# Print current game board

def board():
    
    print(" {s1} | {s2} | {s3}".format(s1 = spaces['m1'], s2 = spaces['m2'], s3 = spaces['m3']))
    
    print("---+---+---")
    
    print(" {s4} | {s5} | {s6}".format(s4 = spaces['m4'], s5 = spaces['m5'], s6 = spaces['m6']))
    
    print("---+---+---")
    
    print(" {s7} | {s8} | {s9}".format(s7 = spaces['m7'], s8 = spaces['m8'], s9 = spaces['m9']))


# To begin game again, reinitialize appropriate parameters

def start_game():
    
    global game_over
    
    global move_count
    
    global spaces
    
    global p_turn
    
    game_over = False
    
    move_count = 0
    
    spaces = {
        'm1': 1,
        'm2': 2,
        'm3': 3,
        'm4': 4,
        'm5': 5,
        'm6': 6,
        'm7': 7,
        'm8': 8,
        'm9': 9,
    }
    
    p_turn = {'name': '', 'symbol': ''}
    
    welcome()
    
    while game_over == False:
    
        board()
    
        get_input()
    
        game_over_check()
    
        swap_player()


# Check for gameover conditions
    
def game_over_check():
    
    global spaces
    
    global game_over
    
    global p_turn
    
    global move_count
   
    move_count += 1
    
    if ((spaces['m1'] == spaces['m2'] == spaces['m3']) or 
        (spaces['m4'] == spaces['m5'] == spaces['m6']) or 
        (spaces['m7'] == spaces['m8'] == spaces['m9']) or 
        (spaces['m1'] == spaces['m4'] == spaces['m7']) or 
        (spaces['m2'] == spaces['m5'] == spaces['m8']) or 
        (spaces['m3'] == spaces['m6'] == spaces['m9']) or 
        (spaces['m1'] == spaces['m5'] == spaces['m9']) or 
        (spaces['m3'] == spaces['m5'] == spaces['m7'])):
        
            clear_output()
        
            board()
            
            print '{x} wins!'.format(x = p_turn['name'])
            
            game_over = True
            
    if (move_count == 9):
        
        print 'Game ended in a tie!'
        
        game_over = True
    
    if game_over == True:
        decision_made = False
        
        while decision_made == False:

            user_input = raw_input("Would you like to play again? (Please enter 'y' or 'n'): ")

            if user_input == 'y':
                
                clear_output()
                
                start_game()
                
                decision_made = True
                
            elif user_input == 'n':
                
                raise SystemExit('Thanks for playing!')
                

# Verify is an integer, apply to user input for space selection

def is_int(x):
    
    try: 
        
        int(x)
        
        return True
    
    except ValueError:
        
        return False
    

# Get input from user and run checks for valid selection

def get_input():
    
    user_input_int = ''
    
    good_input = False
    
    global spaces
    
    while good_input == False:
        
        user_input_str = raw_input('{p_name}, please pick a free space from 1 to 9 to place {p_symbol}: '.format(p_name = p_turn['name'], p_symbol = p_turn['symbol']))
        
        if is_int(user_input_str) == True:
            
            user_input_int = int(user_input_str)
            
        m_name = 'm' + user_input_str
    
        if ((is_int(user_input_int) == False) or (user_input_int < 1) or (user_input_int > 9)):
            
            user_input = raw_input('{p_name}, please pick a free space from 1 to 9 to place {p_symbol}: '.format(p_name = p_turn['name'], p_symbol = p_turn['symbol']))
            
        elif ((is_int(user_input_int) == True) and 
              
              (user_input_int >= 1) and 
              
              (user_input_int <= 9) and 
              
              (is_int(spaces[m_name]))):
            
            good_input = True
            
            spaces[m_name] = p_turn['symbol']


# main loop

start_game()


    





