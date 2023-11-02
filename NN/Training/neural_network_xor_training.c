#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double dSigmoid(double x) { return x * (1 - x); }

double init_weight() { return ((double)rand())/((double)RAND_MAX); }

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}


#define numInputs 2
#define numHiddenNodes 2
#define numOutputs 1
#define numTrainingSets 4

int main (void) {

    const double lr = 0.1f;
    
    double hiddenLayer[numHiddenNodes];
    double outputLayer[numOutputs];
    
    double hiddenLayerBias[numHiddenNodes];
    double outputLayerBias[numOutputs];

    double hiddenWeights[numInputs][numHiddenNodes];
    double outputWeights[numHiddenNodes][numOutputs];
    

    double training_inputs[numTrainingSets][numInputs] = {{0.0f,0.0f},
                                                          {1.0f,0.0f},
                                                          {0.0f,1.0f},
                                                          {1.0f,1.0f}};
    double training_outputs[numTrainingSets][numOutputs] = {{0.0f},
                                                            {1.0f},
                                                            {1.0f},
                                                            {0.0f}};
    
    for (int i=0; i<numInputs; i++) {
        for (int j=0; j<numHiddenNodes; j++) {
            hiddenWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numHiddenNodes; i++) {
        hiddenLayerBias[i] = init_weight();
        for (int j=0; j<numOutputs; j++) {
            outputWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numOutputs; i++) {
        outputLayerBias[i] = init_weight();
    }
    
    int trainingSetOrder[] = {0,1,2,3};


    
    int numberOfEpochs;
    char input[50];

    while (1) {
        printf("Please enter the number of epochs between 10,000 and 20,000,000: ");
        fgets(input, 50, stdin);

        char *end;
        numberOfEpochs = strtol(input, &end, 10);

        if (*end != '\n') {
            printf("Invalid input. Please enter an integer.\n");
            continue;
        }

        if (numberOfEpochs < 10000 || numberOfEpochs > 20000000) {
            printf("Invalid input. The number of epochs must be between 10,000 and 20,000,000.\n");
            continue;
        }

        break;
    }

    for(int epochs=0; epochs < numberOfEpochs; epochs++) {

        shuffle(trainingSetOrder,numTrainingSets); 

        for (int x=0; x<numTrainingSets; x++) {
            
            int i = trainingSetOrder[x];
            
            


            for (int j=0; j<numHiddenNodes; j++) {
                double activation = hiddenLayerBias[j];
                 for (int k=0; k<numInputs; k++) {
                    activation += training_inputs[i][k] * hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }
            
            for (int j=0; j<numOutputs; j++) {
                double activation = outputLayerBias[j];
                for (int k=0; k<numHiddenNodes; k++) {
                    activation += hiddenLayer[k] * outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            }
            
            // Print the results from forward pass
                ///printf ("Input:%g  Input:%g    Expected Output: %g  Result : %g\n",
                   /// training_inputs[i][0], training_inputs[i][1],
                    ///training_outputs[i][0],outputLayer[0]);



            
            double deltaOutput[numOutputs];
            for (int j=0; j<numOutputs; j++) {
                double errorOutput = (training_outputs[i][j] - outputLayer[j]);
                deltaOutput[j] = errorOutput * dSigmoid(outputLayer[j]);
            }
            
            double deltaHidden[numHiddenNodes];
            for (int j=0; j<numHiddenNodes; j++) {
                double errorHidden = 0.0f;
                for(int k=0; k<numOutputs; k++) {
                    errorHidden += deltaOutput[k] * outputWeights[j][k];
                }
                deltaHidden[j] = errorHidden * dSigmoid(hiddenLayer[j]);
            }
            
            for (int j=0; j<numOutputs; j++) {
                outputLayerBias[j] += deltaOutput[j] * lr;
                for (int k=0; k<numHiddenNodes; k++) {
                    outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * lr;
                }
            }
            
            for (int j=0; j<numHiddenNodes; j++) {
                hiddenLayerBias[j] += deltaHidden[j] * lr;
                for(int k=0; k<numInputs; k++) {
                    hiddenWeights[k][j] += training_inputs[i][k] * deltaHidden[j] * lr;
                }
            }
        }
    
    }

    fputs ("Final Hidden Weights\n[ ", stdout);
    for (int j=0; j<numHiddenNodes; j++) {
        fputs ("[ ", stdout);
        for(int k=0; k<numInputs; k++) {
            printf ("%f ", hiddenWeights[k][j]);
        }
        fputs ("] ", stdout);
    }
    
    fputs ("]\nFinal Hidden Biases\n[ ", stdout);
    for (int j=0; j<numHiddenNodes; j++) {
        printf ("%f ", hiddenLayerBias[j]);
    }

    fputs ("]\nFinal Output Weights", stdout);
    for (int j=0; j<numOutputs; j++) {
        fputs ("[ ", stdout);
        for (int k=0; k<numHiddenNodes; k++) {
            printf ("%f ", outputWeights[k][j]);
        }
        fputs ("]\n", stdout);
    }

    fputs ("Final Output Biases\n[ ", stdout);
    for (int j=0; j<numOutputs; j++) {
        printf ("%f ", outputLayerBias[j]);
        
    }
    
    fputs ("]\n", stdout);

    return 0;
    
}