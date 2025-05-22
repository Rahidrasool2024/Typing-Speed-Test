#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define RESET   "\x1B[0m"

char sentences[][100] = {
    "The quick brown fox jumps over the lazy dog and ran away very fast",
    "C programming is fun and challenging but it is very close to computer",
    "Practice makes a man perfect and procrastination makes a man unproductive",
    "Hello world! This is a typing speed test but it is very fun to do",
    "The five boxing wizards jump quickly to catch a white mouse falling from the tree",
    "How vexingly quick daft zebras jump into the river to run from the lion",
    "Pack my box with five dozen bananas as im doing bulking to gain more weight.",
    "A journey of a thousand miles begins with a single step forward",
    "The early bird catches the worm but the second mouse gets the cheese",
    "All that glitters is not gold especially in this modern economy",
    "Every cloud has a silver lining if you look closely enough",
    "Fortune favors the bold who take risks and work hard",
    "Great minds think alike but fools rarely differ in opinion",
    "Honesty is the best policy when dealing with business partners",
    "If the shoe fits wear it with confidence and style",
    "Knowledge is power that cannot be taken away from you",
    "Laughter is the best medicine for stress and anxiety",
    "Many hands make light work when organized properly",
    "No pain no gain applies to both fitness and career",
    "Opportunities don't happen you create them yourself",
    "Practice what you preach to maintain credibility",
    "Quality is better than quantity in most situations",
    "Rome wasn't built in a day and neither are skills",
    "Slow and steady wins the race in the long run",
    "The pen is mightier than the sword in modern times",
    "United we stand divided we fall as history shows",
    "Variety is the spice of life that keeps things interesting",
    "When in Rome do as the Romans do to fit in",
    "You can't judge a book by its cover alone",
    "Zeal without knowledge is like a ship without a rudder",
    "Actions speak louder than words in all relationships",
    "Better late than never applies to learning new skills",
    "Curiosity killed the cat but satisfaction brought it back",
    "Don't count your chickens before they hatch fully",
    "Efficiency is doing things right the first time"
};

const char* get_random_sentence() {
    int total_sentences = sizeof(sentences) / sizeof(sentences[0]);
    return sentences[rand() % total_sentences];
}

int count_correct_chars(const char *target, const char *input) {
    int correct = 0;
    for (int i = 0; i < strlen(target) && i < strlen(input); i++) {
        if (input[i] == target[i]) correct++;
    }
    return correct;
}

void display_results(double time_sec, int correct, int total_chars) {
    double wpm = (correct / 5.0) / (time_sec / 60.0);
    double accuracy = (double)correct / total_chars * 100;
    
    printf("\n\n" BLUE "===== Results =====\n" RESET);
    printf("Time taken: %.2f seconds\n", time_sec);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Speed: %.2f WPM\n", wpm);
    
    if (wpm > 40) printf(GREEN "Excellent typing speed!\n" RESET);
    else if (wpm > 30) printf(GREEN "Good job!\n" RESET);
    else printf(YELLOW "Keep practicing!\n" RESET);
}

void highlight_errors(const char *target, const char *input) {
    printf("\n" BLUE "Errors highlighted:\n" RESET);
    printf("Original: %s\n", target);
    printf("Your text: ");
    
    for (int i = 0; i < strlen(target); i++) {
        if (i >= strlen(input)) {
            printf(RED "%c" RESET, target[i]);
        } else if (input[i] != target[i]) {
            printf(RED "%c" RESET, input[i]);
        } else {
            printf(GREEN "%c" RESET, input[i]);
        }
    }
    printf("\n");
}

int main() {
    srand(time(0));
    const char *target = get_random_sentence();
    int target_length = strlen(target);
    
    printf(BLUE "===== Typing Speed Test =====\n" RESET);
    printf("Type the following sentence:\n\n");
    printf("%s\n\n", target);
    
    printf("Press ENTER when ready to start typing...");
    while (getchar() != '\n');
    
    printf("\nStart typing now!\n");
    
    clock_t start = clock();
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    clock_t end = clock();
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    
    int correct = count_correct_chars(target, input);
    
    display_results(time_sec, correct, target_length);
    highlight_errors(target, input);
    
    return 0;
}