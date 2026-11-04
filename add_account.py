import pickle
import time

with open('acc.txt', 'ab') as g:
    newly_added = []
    while True:
        email = str(input('Enter Email: '))
        pas = str(input('Enter Password: '))
        pickle.dump([email, pas], g)
        newly_added.append([email, pas])
        ab = input(f'\nDo you want to add more accounts?[y/n]: ')
        if 'y' in ab:
            pass
        else:
            print("Account Saved")
            g.close()
            time.sleep(3)
            break
