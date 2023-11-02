#include <stdio.h>
#include <math.h>
#include "math_functions.h"
#include <string.h> 

int main() {
    double hidden_weights[2][2] = {{6.615498, 6.616239}, {8.354189, 8.357140}};
    double hidden_biases[2] = {-10.095576, -3.896073};
    double output_weights[2] = {-17.528800, 16.956187};
    double output_bias = -8.193561;

    char input[3];
    int ret;
    while(1) {
        printf("Enter your 2 inputs (10, 01, 11, or 00) or 'q' to quit: ");
        ret = scanf("%s", input);
        while(getchar() != '\n'); // clear input buffer

        if(input[0] == 'q') {
            return 0;
        }

        if(ret != 1 || strlen(input) != 2 || (input[0] != '0' && input[0] != '1') || (input[1] != '0' && input[1] != '1')) {
            continue;
        }

        int input1 = input[0] - '0';
        int input2 = input[1] - '0';

        double inputs[2] = {input1, input2};

        double hidden_layer_output[2];
        for(int i = 0; i < 2; i++) {
            hidden_layer_output[i] = sigmoid(hidden_weights[i][0]*inputs[0] + hidden_weights[i][1]*inputs[1] + hidden_biases[i]);
        }

        double output = sigmoid(output_weights[0]*hidden_layer_output[0] + output_weights[1]*hidden_layer_output[1] + output_bias);

        printf("Output: %d\n", output >= 0.5 ? 1 : 0);
        printf("Confidence: %.5f%%\n", output * 100);
    }

    return 0;
}
