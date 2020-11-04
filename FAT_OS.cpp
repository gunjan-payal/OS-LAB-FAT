#include<iostream>
#include<vector>

using namespace std;

int LFU_FIFO(vector<int> sequence, int buffer_size){
    int page_faults = 0;
    vector<int> buffer_stack;
    vector<int> frequency_stack;
    for(int i=0;i<sequence.size();i++){
        // first, we will have page faults because the frame has no elements
        if(buffer_stack.size()<buffer_size){
            page_faults++;
            cout<<"Page Fault NO ELEMENT"<<endl;
            buffer_stack.push_back(sequence[i]);
            frequency_stack.push_back(0);
        }
        else{
            //page hit
            int page_hit = 0;
            for(int j=0;j<buffer_stack.size();j++){
                if(buffer_stack[j]==sequence[i]){
                    cout<<"Page Hit"<<endl;
                    page_hit = 1;
                    int freq_val = frequency_stack[j];
                    frequency_stack[j] = frequency_stack[j] + 1;
                    break;
                }
            }
            //page fault has occured
            if(page_hit==0){
                page_faults++;
                cout<<"Page Fault"<<endl;
                int min_freq = 0;
                int same_freq = 0;
                for(int k=0;k<frequency_stack.size();k++){
                    if(frequency_stack[k]<frequency_stack[min_freq]){
                        min_freq = k;
                    }
                }
                for(int k=0;k<frequency_stack.size();k++){
                    if(frequency_stack[min_freq]==frequency_stack[k] & min_freq!=k){
                        same_freq = 1;
                    }
                }
                //min frequency will determine which page will be evicted
                //no need to invoke secondary page replacement algorithm
                if(same_freq==0){
                    cout<<"No need to apply FIFO"<<endl;
                    cout<<"Eliminated "<<buffer_stack[min_freq]<<endl;
                    frequency_stack.erase(frequency_stack.begin() + min_freq);
                    buffer_stack.erase(buffer_stack.begin() + min_freq);
                    frequency_stack.push_back(0);
                    buffer_stack.push_back(sequence[i]);
                }
                else if(same_freq==1){
                    //now we will apply LRU logic because LFU logic has failed
                    cout<<"Applied FIFO"<<endl;
                    cout<<"Eliminated "<<buffer_stack[0]<<endl;
                    frequency_stack.erase(frequency_stack.begin());
                    frequency_stack.push_back(0);
                    buffer_stack.erase(buffer_stack.begin());
                    buffer_stack.push_back(sequence[i]);
                }
            }
        }
        
    }
    return page_faults;
} 

int LRU(vector<int> sequence, int buffer_size){
    vector<int> buffer_stack;
    int page_faults = 0;
    for(int i=0;i<sequence.size();i++){
        if(buffer_stack.size()< buffer_size){
            page_faults++;
            cout<<"Page Fault NO ELEMENT"<<endl;
            buffer_stack.push_back(sequence[i]);
        }
        else{
            int page_hit=0;
            for(int j=0;j<buffer_size;j++){
                //page hit
                if(buffer_stack[j]==sequence[i]){
                    cout<<"Page Hit"<<endl;
                    buffer_stack.erase(buffer_stack.begin() + j);
                    buffer_stack.push_back(sequence[i]);
                    page_hit=1;
                    break;
                }
                //page fault
            }
            if (page_hit==0){
                page_faults++;
                cout<<"Page Fault"<<endl;
                //page fault but buffer is full
                buffer_stack.erase(buffer_stack.begin());
                buffer_stack.push_back(sequence[i]);
            }
        }
    }
    return page_faults;    
}
int FIFO(vector<int> sequence, int buffer_size){
    vector<int> buffer_stack;
    int page_faults = 0;
    for(int i=0;i<sequence.size();i++){
        if(buffer_stack.size()< buffer_size){
            page_faults++;
            cout<<"Page Fault NO ELEMENT"<<endl;
            buffer_stack.push_back(sequence[i]);
        }
        else{
            int page_hit=0;
            for(int j=0;j<buffer_size;j++){
                //page hit
                if(buffer_stack[j]==sequence[i]){
                    cout<<"Page Hit"<<endl;
                    page_hit=1;
                    break;
                }
                //page fault
            }
            if (page_hit==0){
                page_faults++;
                cout<<"Page Fault"<<endl;
                //page fault but buffer is full
                buffer_stack.erase(buffer_stack.begin());
                buffer_stack.push_back(sequence[i]);
            }
        }
    }
    return page_faults;
}

int main(){
    int num_el;
    int buffer_size = 0;
    int choice;
    vector<int> seq;
    cout<<"Enter the number of elements in the reference string:";
    cin>>num_el;
    for(int i=0;i<num_el;i++){
        cout<<"Enter element number "<<i+1<<":";
        int tmp_inp;
        cin>>tmp_inp;
        seq.push_back(tmp_inp);
    }
    cout<<"Enter Buffer Size:";
    cin>>buffer_size;
    int choice1 = 0;
    int choice2 = 0;
    cout<<"Select the algorithm that you want to apply:"<<endl;
    cout<<"**1 for FIFO**"<<endl;
    cout<<"**2 for LRU**"<<endl;
    cout<<"**3 for LFU_FIFO**"<<endl;
    cin>>choice;
    if(choice==1){
        int pf = FIFO(seq,buffer_size);
        cout<<"TOTAL FAULTS:"<<pf;
    }
    else if(choice==2){
        int pf = LRU(seq,buffer_size);
        cout<<"TOTAL FAULTS:"<<pf;
    }
    else if(choice==3){
        int pf = LFU_FIFO(seq,buffer_size);
        cout<<"TOTAL FAULTS:"<<pf;
    }
    else{
        cout<<"INVALID INPUT PROVIDED"<<endl;
    }
    return 0;
}