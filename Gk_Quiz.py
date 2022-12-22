print("Welcome to the General Knowledge Quiz!")
playing=input("Do you want to play, type Yes/No. ")
if playing.lower() !="yes":
    quit()
else:
    print("Okay then, Let's Play!!!")
    print("You'll get 5 points for each correct answer!\n")
point = 0

solution1=input("Q.1- What is the capital of Egypt? ")
if solution1.lower() == "cairo":
    print("Your answer is correct!")
    point += 5
else:
        print("Sorry, your answer is incorrect")


solution2=input("Q.2- Which is the most sensitive organ in our body? ")
if solution2.lower() == "skin":
    print("Your answer is correct!")
    point += 5
else:
        print("Sorry, your answer is incorrect")


solution3=input("Q.3- Who is known as the Iron Man of India? ")
if solution3.lower() == "sardar vallabhbhai patel":
    print("Your answer is correct!")
    point+=5
else:
        print("Sorry, your answer is incorrect")


solution4=input("Q.4- Who was the first women to receive Bharat Ratna? ")
if solution4.lower() == "indira gandhi":
    print("Your answer is correct!")
    point+=5
else:
        print("Sorry, your answer is incorrect")


solution5=input("Q.5- What is the full form of LAN? ")
if solution5.lower() == "local area network":
    print("Your answer is correct!")
    point+=5
else:
        print("Sorry, your answer is incorrect")


print("Your score is %d" %point )
print("You have got "+ str((point/25)*100) + "%") 