from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support import expected_conditions as EC
import time
import threading
import keyboard
import pickle

# Path to your WebDriver (e.g., chromedriver)
driver_path = "E:/Program Files/chromedriver-win64/chromedriver.exe"

# Flag to control when to stop scrolling
stop_script = False

def stop_on_esc():
    global stop_script
    keyboard.wait('esc')  # Wait for the user to press the Esc key
    stop_script = True 

# Initialize the WebDriver
service = Service(driver_path)
chrome_options = Options()
prefs = {"profile.default_content_setting_values.notifications": 2}  # 2 = Block notifications
chrome_options.add_experimental_option("prefs", prefs)
drivers = []

urls = []

accounts = []
h = open('acc.txt', 'rb')
while True:
    try: 
        accounts.append(pickle.load(h))
    except EOFError:
        break
h.close()

n_bot = int(input("Enter Number of Bot: "))

if n_bot > len(accounts):
    n_bot = len(accounts)

for i in range(n_bot):
    tmp = input("Enter Url: ")
    urls.append(tmp)

for i in range(n_bot):
    drivers.append(webdriver.Chrome(service=service, options=chrome_options))

for driver in drivers:
    driver.get("https://www.facebook.com")

if len(accounts) == 0:
    print('There are no accounts! Please add some and retry')
    time.sleep(3)
else:
    for i in range(len(drivers)):
        email = str(accounts[i][0])
        pas = str(accounts[i][1])         
        username = drivers[i].find_element(By.ID, "email")
        password = drivers[i].find_element(By.ID, "pass")
        username.send_keys(email)
        password.send_keys(pas)
        password.send_keys(Keys.RETURN)

    time.sleep(20)

    try:
        
        for i in range(len(drivers)):
            drivers[i].get(urls[i])
        print(f"Opened URL: {urls[i]}")
        
        listener_thread = threading.Thread(target=stop_on_esc)
        listener_thread.daemon = True 
        listener_thread.start()

        print("Scrolling down the page... Press Esc to stop.")
        scroll_pause_time = 1 

        while not stop_script:  
            for driver in drivers:
                try: 
                    print("Scrollable element found. Scrolling within the element.")
                    scrollable_element = driver.find_element(
                        By.CSS_SELECTOR,
                        "div.xb57i2i.x1q594ok.x5lxg6s.x78zum5.xdt5ytf.x6ikm8r.x1ja2u2z.x1pq812k.x1rohswg.xfk6m8.x1yqm8si.xjx87ck.xx8ngbg.xwo3gff.x1n2onr6.x1oyok0e.x1odjw0f.x1iyjqo2.xy5w88m"
                    )
                    driver.execute_script("arguments[0].scrollTop += 500;", scrollable_element)
                except Exception as e:
                    print(f"Scrollable element not found. Falling back to normal scroll. Error: {e}")
                    driver.execute_script("window.scrollBy(0, 500);")
            time.sleep(scroll_pause_time)

        print("Scrolling stopped by user!")

        for index, driver in enumerate(drivers):
            body_content = driver.find_element(By.TAG_NAME, "body").get_attribute("outerHTML")
            
            with open(f"input{index}.txt", "w", encoding="utf-8") as file:
                file.write(body_content)

    finally:
        # Close the browser
        for driver in drivers:
            driver.quit()
