// Ian Rapoport
// irapopor
// 12B
// 9 May 2016
// Simulation.java
// Simulation program for pa4 that processes Jobs while putting them in Queues

import java.io.*;
import java.util.Scanner;

public class Simulation{

   public static Job getJob(Scanner in) {
      String[] s = in.nextLine().split(" ");
      if(! s[0].equals("")){
        int a = Integer.parseInt(s[0]);
        int d = Integer.parseInt(s[1]);
        return new Job(a, d);
      }else{
        return null;
      }
   }

   public static void main(String[] args) throws IOException{

      // Check length of arguments
      if( args.length != 1 ){
        System.out.println("Usage: FileCopy <input file>");
        System.exit(1);
      }

      // Open input file, intialize Scanner and create output files
      Scanner in = new Scanner(new File(args[0]));
      PrintWriter rptOut = new PrintWriter(new FileWriter(args[0]+".rpt"));
      PrintWriter trcOut = new PrintWriter(new FileWriter(args[0]+".trc"));

      // Declare variables
      String line = in.nextLine().trim();
      int numJobs = Integer.parseInt(line); 
      int totalWait, maxWait, shortestQueueLength, time, temp;
      double averageWait;
      Queue[] processors = new Queue[numJobs];
      Queue[] inLine = new Queue[numJobs];
      processors[0] = new Queue();
      inLine[0] = new Queue();
      boolean stillProcessing;
      Job storage = null;

      // Fill first Queue in Queue array 
      // with Jobs as orinally stated in input file
      while( in.hasNextLine() ){
        storage = getJob(in);
        if(storage != null){
          processors[0].enqueue(storage);
        }
      }

      // Print headings to output files
      rptOut.println("Report file: "+args[0]+".rpt"); //
      trcOut.println("Trace file: "+args[0]+".trc");
      rptOut.println(numJobs + " Jobs:");
      trcOut.println(numJobs + " Jobs:");
      rptOut.println(processors[0]);
      trcOut.println(processors[0]);
      rptOut.println();
      trcOut.println();
      for(int i=0; i<59; i++){
        rptOut.print("*");
      }
      rptOut.println();

      // Loop for different number of processors
      for(int n=1; n<numJobs; n++){

        // Print more data to Output files
        for(int i=0; i<29; i++){
          trcOut.print("*");
        }
        trcOut.println();
        if(n==1){
          trcOut.println(n + " processor:");
        }else{
          trcOut.println(n + " processors:");
        }
        for(int i=0; i<29; i++){
          trcOut.print("*");
        }
        trcOut.println();

        // Reset values for next loop
        for(int c=1; c<=n; c++){
          processors[c] = new Queue();
          inLine[c] = new Queue();
        }
        stillProcessing = true;
        time = 0;

        // Loop for each processor
        while(stillProcessing){

          // Calculate finish time for Jobs first in line at processor
          // Moves Jobs up in line
          for(int m=1; m<=n; m++){
            if(processors[m].length() != 0){
              while(((Job)processors[m].peek()).getFinish() == time){
                storage = (Job)processors[m].dequeue();
                processors[0].enqueue(storage);
                if(inLine[m].length() != 0){
                  storage = (Job)inLine[m].dequeue();
                  storage.computeFinishTime(time);
                  processors[m].enqueue(storage);
                }else break;
              }
            }
          }

          // Move Jobs from storage Queue in line for processor if it is their
          // arrival time
          if(!processors[0].isEmpty()){
            while(((Job)processors[0].peek()).getArrival() == time){
              shortestQueueLength = processors[1].length()+inLine[1].length();
              for(int k=2; k<=n; k++){
                if(processors[k].length()+inLine[k].length() < shortestQueueLength){
                  shortestQueueLength = processors[k].length()+inLine[k].length();
                }
              }
              for(int l=1; l<=n; l++){
                if(processors[l].length()+inLine[l].length() == shortestQueueLength){
                  storage = (Job)processors[0].dequeue();
                  if(processors[l].length() == 0){
                    storage.computeFinishTime(time);
                    processors[l].enqueue(storage);
                  }else{
                    inLine[l].enqueue(storage); 
                  } 
                  break;
                }
              }
              if(processors[0].length() == 0) break;
            }
          }

          // Prints current position of Jobs with time to trace file
          trcOut.println("time="+time);
          for(int i=0; i<=n; i++){
            trcOut.println(i + ": "+processors[i]+inLine[i]);
          }
          trcOut.println();

          // Checks if there are still jobs to process
          if(processors[0].length() != 0){
            if(((Job)processors[0].peek()).getFinish() != -1){
              stillProcessing = false;
              for(int b=1; b<=n; b++){
                if(processors[b].length() != 0){
                  stillProcessing = true;
                  break;
                }
              }
            } 
          }
          
          // Calculates totalWait, maxWait and averageWait and prints data to
          // report if there are no longer jobs to be processed
          if(!stillProcessing){
            storage = (Job)processors[0].dequeue();
            maxWait = storage.getWaitTime();
            totalWait = maxWait;
            while(!processors[0].isEmpty()){
              storage = (Job)processors[0].dequeue();
              totalWait += storage.getWaitTime();
              if(storage.getWaitTime() > maxWait){
                maxWait = storage.getWaitTime();
              }
            }
            averageWait = totalWait/((double)numJobs);
            String aW = String.format("%.02f", averageWait);
            if(n==1){
              rptOut.println(n+" processor: totalWait="+totalWait+", maxWait="+maxWait+", averageWait="+aW);
            }else{
              rptOut.println(n+" processors: totalWait="+totalWait+", maxWait="+maxWait+", averageWait="+aW);
            }
            break;
          }

          // Calculates time for next loop for which something happens
          if(processors[0].length() != 0){
            if(((Job)processors[0].peek()).getFinish() == -1 ){
              storage = (Job)processors[0].peek();
              time = storage.getArrival();
            }else{
              for(int y=1; y<=n; y++){
                if(processors[y].length() != 0){
                  time = ((Job)processors[y].peek()).getFinish();
                  break;
                }
              }
            }
          }else{
            for(int z=1; z<=n; z++){
              boolean timeChanged = false;
              if(timeChanged == false){
                if(processors[z].length() != 0){
                  time = ((Job)processors[z].peek()).getFinish();
                  timeChanged = true;
                }
              }else{
                temp = ((Job)processors[z].peek()).getFinish();
                if(temp<time) time = temp;
              }
            }
          }
          for(int c=1; c<=n; c++){
            if(processors[c].length() == 1){
              storage = (Job)processors[c].peek();
              temp = storage.getFinish();
              if(temp < time) time = temp;
            }
          }

        }

      // Reset storage Queue to original jobs
      in = null;
      in = new Scanner(new File(args[0]));
      in.nextLine().trim();
      while(in.hasNextLine()){
        storage = getJob(in);
        if(storage != null){
          processors[0].enqueue(storage);
        }
      }

    }

      // Close files and end
      in.close();
      rptOut.close();
      trcOut.close();
      
   }
}

