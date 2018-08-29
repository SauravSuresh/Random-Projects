from IPython.display import clear_output
from random import randint

brd=['1','2','3','4','5','6','7','8','9']
d={1:'',2:''}
active_player=0
turns=0


def active_change():
    global active_player
    if active_player==1:
        active_player=2
    else:
        active_player=1


def win():
    active_change()
    print(f'{active_player} won!')
    

def check():
    return (brd[0]==brd[1]==brd[2])or(brd[3]==brd[4]==brd[5])or(brd[6]==brd[7]==brd[8])or(brd[0]==brd[4]==brd[8])or(brd[2]==brd[4]==brd[6])or(brd[0]==brd[3]==brd[6])or(brd[1]==brd[4]==brd[7])or(brd[2]==brd[5]==brd[8])


def show_board():
    print(f'{brd[6]}|{brd[7]}|{brd[8]}\n{brd[3]}|{brd[4]}|{brd[5]}\n{brd[0]}|{brd[1]}|{brd[2]}')

def player_sel():
    global turns
    global active_player
    while check()!=True:
        if turns==0:
            active_player=randint(1,2)
            print(f'player {active_player} goes first ')
            d[active_player]=input('x/o ?: ')
            if active_player==1:
                if d[1]=='x':
                    d[2]='o'
                else:
                    d[2]='x'
            else:
                if d[2]=='x':
                    d[1]='o'
                else:
                    d[1]='x'
        
        show_board()
        print(f'\n{active_player}')
        slot=int(input(f'player {active_player} goes now: '))-1
        brd[slot]=d[active_player]
        clear_output()
        turns+=1
        active_change()
    else:
        win()
   

player_sel()