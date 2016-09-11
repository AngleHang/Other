import java.util.*;
import java.io.*;
public class EnglishPractice{
   public static void main(String args[]){
      File file_in=new File("text.txt");
      File file_out=new File("answer.txt");
      try{
         Scanner sc=new Scanner(file_in);
         FileWriter out=new FileWriter(file_out);
         BufferedWriter writer=new BufferedWriter(out);
         Scanner reader=new Scanner(System.in);
         int wordnumber=0,rightnumber=0;
         String s=null;
         String word=null;
         while(sc.hasNext()){
            s=s+" "+sc.next();
            wordnumber++;
         }
         s=s.substring(5);
         System.out.println("一共有"+wordnumber+"道题需要练习.");
         sc=new Scanner(s);
         for(int i=1;sc.hasNext();i++){
            s=sc.next();
            System.out.print("您有5秒的时间记忆单词："+s);
            Thread.sleep(5000);
            System.out.print("\r");
            for(int j=0;j<=30;j++)System.out.print("*");
            System.out.println("");
      	    System.out.print("5秒时间已过，请默写出刚刚显示的单词并按回车确定：");
            word=reader.nextLine();
            writer.write(i+" "+word);
            writer.newLine();
            writer.flush();
            if(word.equals("\n"))System.out.println("您没有输入任何单词");
            else if(word.equals(s)){
                System.out.println("恭喜 ，单词默写正确！");
                rightnumber++;
            }
            else System.out.println("抱歉，单词默写错误！");
            System.out.println("已默写了"+i+"个单词");
            System.out.println("默写正确"+rightnumber+"个单词");
            System.out.printf("当前正确率为%.2f%%\n\n",rightnumber*100.0/i);
            Thread.sleep(1000);
         }
         System.out.printf("练习结束\n本次练习%d个单词，共默写正确%d个，总正确率为%.2f%%\n",wordnumber,rightnumber,rightnumber*100.0/wordnumber);
         writer.close();
      }
      catch(Exception ext){
         System.out.println(ext);
      }
   }
}
