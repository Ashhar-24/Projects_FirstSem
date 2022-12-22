answer=randi(50);

numofGuesses=0;

guess=-1;
while (guess ~= answer)
    numofGuesses = numofGuesses+1;

    guess= input('Guess a number between 1 and 50!: ');
    if guess < answer 
        fprintf('Your guess [%i] is too low!!\n', guess);
    elseif guess > answer
        fprintf('Your guess [%i] is too high!!\n', guess);
    else 
        fprintf('Congratulations! You have guessed the correct number [%i]\n', answer);
        fprintf('It took you %i guesses to get it right',numofGuesses);
    end
end 
