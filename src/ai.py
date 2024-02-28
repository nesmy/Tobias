import pyttsx3
import speech_recognition as sr

class AI():
    __name = ""
    __skill = []

    def __init__(self, name=None):
        self.engine = pyttsx3.init()
        self.r = sr.Recognizer()
        self.m = sr.Microphone()
        self.voices = self.engine.getProperty('voices')
        self.engine.setProperty('rate', 140)

        if name is not None:
            self.__name = name

        print("Listening")
        with self.m as source:
            self.r.adjust_for_ambient_noise(source)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        sentence = "Hello, my name is" + self.__name
        self.__name = value
        self.engine.say(sentence)
        self.engine.runAndWait()

    def Say(self, sentence):
        self.engine.say(sentence)
        self.engine.runAndWait()

    def Listen(self):
        phrase = {
            "success": True,
            "error": None,
            "transcription": None
                }
        print("Say something")
        with self.m as source:
            audio = self.r.listen(source)
        print("got it: ")
        try:
            phrase["transcription"] = self.r.recognize_google(audio)
            print(phrase["transcription"])
        except sr.RequestError:
            phrase["success"] = False
            phrase["error"] = "API unavailable"
        except sr.UnknownValueError:
            phrase["error"] = "Unable to recognize speech"
            print(phrase["error"])

        return phrase["transcription"]
