from ai import AI
import pyjokes

Tobias = AI()

def joke():
    funny = pyjokes.get_joke()
    print(funny)
    Tobias.Say(funny)

welcome = "Hello my name is Tobias, a tool box assistant. At your service!"

Tobias.Say(welcome)

command = ""
while True and command != "goodbye":
    command = Tobias.Listen()
    print("command was:", command)

    if command == "tell me a joke":
        joke()

Tobias.Say("Goodbye! I'm going to sleep now!")
    
