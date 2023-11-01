/**********
© Copyright 2020 Xilinx, Inc.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**********/
#include "adf.h"

void VecReduce(input_window<int32> *in1,input_window<int32> *in2, output_window<int32> *out) 
{
    int32 wsum = 0;
    int32 val1=0;
    int32 val2=0;
    for (unsigned i = 0; i < 128; i++) 
    {

        window_readincr(in1, val1);
        window_readincr(in2, val2);
        wsum = wsum + (val1 * val2);
    }
    window_write(out, wsum);
}
