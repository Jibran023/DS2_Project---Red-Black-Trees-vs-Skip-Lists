import random
import string

# Generate a string of 5000 random letters (uppercase and lowercase)
letters_1000 = ''.join(random.choice(string.ascii_letters) for _ in range(1000))

# Save the generated string to a text file
with open('letters_1000.txt', 'w') as file:
    file.write(letters_1000)

print("1000 random letters have been saved to letters.txt.")
