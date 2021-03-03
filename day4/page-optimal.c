#include<stdio.h>
 
int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < no_of_pages; ++i){
        scanf("%d", &pages[i]);
    }
    //storing all frames as -1
    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;
        //if we alredy have page in frame
        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        //flag2 check if there is empty frame (-1)
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        //temp stores an array of length equal to frames 
        //and its values are postion of next occurence of frames
        if(flag2 == 0){
        	flag3 =0;
        	
            for(j = 0; j < no_of_frames; ++j){
            	temp[j] = -1;
            	
            	for(k = i + 1; k < no_of_pages; ++k){
            		if(frames[j] == pages[k]){
            			temp[j] = k;
            			break;
            		}
            	}
            }
            //flag 3 checks if temp is empty(-1)
            for(j = 0; j < no_of_frames; ++j){
            	if(temp[j] == -1){
            		pos = j;
            		flag3 = 1;
            		break;
            	}
            }
            //if temp is not empty then need to find position of frame 
            //which repeats  at far end  of remaining pages
            if(flag3 ==0){
            	max = temp[0];
            	pos = 0;
            	
            	for(j = 1; j < no_of_frames; ++j){
            		if(temp[j] > max){
            			max = temp[j];
            			pos = j;
            		}
            	}            	
            }
            //changing frame at the position
			
			frames[pos] = pages[i];
			faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}