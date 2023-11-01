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
        sum += din1[i] * din2[i]; 
		
	}
    *(dout)=sum;
}
const int ITERATION=1;
const int BLOCK_SIZE_in_Bytes=ITERATION*128*4;
int main(int argc, char ** argv) {
    
    gr.init();
    int32* din1Array=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
	int32* din2Array=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* doutArray=(int32*)GMIO::malloc(4);
    int32* doutRef=(int32*)malloc(4);
    std::cout<<"GMIO::malloc completed"<<std::endl;

    int error=0;


    for(int j=0;j<ITERATION*128;j++){
        din1Array[j]=j;
        din2Array[j]=j;
    }

    gr.gmioIn1.gm2aie(din1Array,BLOCK_SIZE_in_Bytes);
    gr.gmioIn2.gm2aie(din2Array,BLOCK_SIZE_in_Bytes);
    gr.run(ITERATION);
    std::cout<<"Run completed";
    gr.gmioOut.aie2gm(doutArray,5*4);

    ref_func(din1Array,din2Array,doutRef,128);

    if(doutArray[0]!=doutRef[0]){
        std::cout<<"ERROR:dout["<<0<<"]="<<doutArray[0]<<",gold="<<doutRef[0]<<std::endl;
        error++;
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
