
/* Defines functions in lr_2d.hpp */

#include "lr_2d.hpp"
#include <cassert>
#define DEBUG

float hypothesis(float x, float m, float c) {
    return (m * x + c);
} 

float cost_function(vector<float> input_x,
                    vector<float> input_y,
                    float m,
                    float c) {
    assert(input_x.size() == input_y.size());
    int n = input_x.size();
    float cost = 0;

    /*
     * Note : n is the number of input points
     * Note : hypothesis h(x) = m * x + c
     * Cost function : summation over all inputs( (h(x) - y) * (h(x) - y) )
     *
     */
    for(int iter = 0; iter < n; iter++) {
        cost += (hypothesis(input_x[iter], m, c) - input_y[iter]) *
                (hypothesis(input_x[iter], m, c) - input_y[iter]); 
    } 
    
    return cost;
}

float cost_function_m_slope(vector<float> input_x,
                            vector<float> input_y,
                            float m,
                            float c) {
    assert(input_x.size() == input_y.size());

    /*
     * Note : n is the number of input points
     * Cost function derivative w.r.t. m : [ (1/2n) * summation over all inputs( (2*m*x*x) + (2*x*x*c) - (2*x*y)) ]
     *
     */
    int n = input_x.size();
    float slope = 0;

    for(int iter = 0; iter < n; iter++) {
        slope +=    (2 * m * input_x[iter] * input_x[iter]) +
                    (2 * input_x[iter] * c) -
                    (2 * input_x[iter] * input_y[iter]);        
    } 
    return (slope * ((float)1 / (float)(2 * n)));
}

float cost_function_c_slope(vector<float> input_x,
                            vector<float> input_y,
                            float m,
                            float c) {
    assert(input_x.size() == input_y.size());

    /*
     * Note : n is the number of input points
     * Cost function derivative w.r.t. c : [ (1/2n) * summation over all inputs((2*c) + (2*m*x) - (2*y)) ]
     *
     */
    int n = input_x.size();
    float slope = 0;

    for(int iter = 0; iter < n; iter++) {
        slope +=    (2 * c) +
                    (2 * m * input_x[iter]) - 
                    (2 * input_y[iter]);
    } 
    return (slope * ((float)1 / (float)(2 * n)));
}

weights perform_linear_regression_2d(  lr_2d_input input,
                                       weights init_weights) {
    assert(input.input_x.size() == input.input_y.size());
    assert(input.input_x.size() > 0);
    /* Randomly init weights */
    weights w = init_weights;
    
    int iter = 0;
    while(iter < input.epoch) {
        float m_slope = cost_function_m_slope(input.input_x, input.input_y, w.m, w.c) * input.learning_rate;
        float c_slope = cost_function_c_slope(input.input_x, input.input_y, w.m, w.c) * input.learning_rate;
        w.m -= m_slope;
        w.c -= c_slope;  
        iter++;

#ifdef DEBUG
        cerr<<"epoch - "<<iter<<" | "<< "cost - "<<cost_function(input.input_x, input.input_y, w.m, w.c)<<endl;
#endif
    }
    
    return w;
}
