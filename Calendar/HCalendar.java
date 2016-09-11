import java.util.Scanner;
public class HCalendar{
   public static void main(String[]args){
      CalendarBean date=new CalendarBean();
      Scanner sc=new Scanner(System.in);
      System.out.print("请输入年份：");
      int year=sc.nextInt();
      System.out.print("请输入月份：");
      int month=sc.nextInt();
      date.setDate(year,month);
      System.out.print("请选择从周日(0)开始或从周一(1)开始：");
      int j=2;
      while(j!=1&&j!=0){
         j=sc.nextInt();
         if(j==0){
            String calendar[]=date.getCalendar();
            char a[]="日一二三四五六".toCharArray();
            for(char i:a)System.out.printf("%3c",i);
            for(int i=0;i<calendar.length;i++){
               if(i%7==0)System.out.printf("\n");
               System.out.printf("%4s",calendar[i]);
            }
         }else if(j==1){
            String calendar[]=date.getCalendar2();
            char a[]="一二三四五六日".toCharArray();
            for(char i:a)System.out.printf("%3c",i);
            System.out.printf("\n");
            for(int i=0;i<calendar.length;i++){
               System.out.printf("%4s",calendar[i]);
               if((i+1)%7==0)System.out.printf("\n");
            }
         }else System.out.print("请重新输入：\n请选择从周日(0)开始或从周一(1)开始：");
      }
   }
}