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
#include <adf.h>
#include "graph.h"
#include <unistd.h>
#include <fstream>

using namespace adf;

mygraph gr;

void ref_func(int32* din1,int32* din2,int32* dout,int size){
    int32_t sum = 0;
	for(int i=0;i<size;i++){
        dout[i]= din1[i] * din2[i]; 	
	}
}
const int ITERATION=1;
const int BLOCK_SIZE_in_Bytes=ITERATION*ELEMENTS*4;
int main(int argc, char ** argv) {
    
    gr.init();
    int32* din1Array=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* din2Array=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* doutArray=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* doutRef=(int32*)malloc(BLOCK_SIZE_in_Bytes);
    std::cout<<"GMIO::malloc completed"<<std::endl;

    int error=0;

    for(int j=0;j<ITERATION*ELEMENTS;j++){
        din1Array[j]=j;
        din2Array[j]=j;
    }
    std::cout<<"Starting the data transfer "<<std::endl;
    gr.gmioIn1.gm2aie(din1Array,BLOCK_SIZE_in_Bytes);
    gr.gmioIn2.gm2aie(din2Array,BLOCK_SIZE_in_Bytes);
    std::cout<<"Starting the kernel execution"<<std::endl;
    gr.run(ITERATION);
    std::cout<<"Run completed"<<std::endl;
    gr.gmioOut.aie2gm(doutArray,BLOCK_SIZE_in_Bytes);

    ref_func(din1Array,din2Array,doutRef,ELEMENTS);

    for(int i=0;i<ELEMENTS;i++){
        if(doutArray[i]!=doutRef[i]){
            std::cout<<"ERROR:dout["<<i<<"]="<<doutArray[i]<<",gold="<<doutRef[i]<<std::endl;
            error++;
        }
    }
    
    std::cout<<"GMIO transactions finished"<<std::endl;

    GMIO::free(din1Array);
    GMIO::free(din2Array);
    GMIO::free(doutArray);
 
    gr.end();
    if(error==0){
	std::cout<<"PASS!"<<std::endl;
    }else{
	std::cout<<"ERROR!"<<std::endl;
    }

    return error;
};
