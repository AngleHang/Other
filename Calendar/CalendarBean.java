import java.util.*;
public class CalendarBean{
   int year=0;
   int day=0;
   int month=0;
   public void setDate(int year,int month){
      this.year=year;
      this.month=month;
      day=setDay(year,month);
   }
   private int setDay(int year,int month){
      int day=0;
      if(month==2){
         if((year%4==0)&&(year%100!=0)||(year%400==0))day=29;
         else day=28;
      }else if(month==4||month==6||month==9||month==11)day=30;
      else day=31;
      return day;
   }
   public String[] getCalendar(){
      String s[]=new String[42];
      Calendar a=Calendar.getInstance();
      a.set(year,month-1,1);
      int weekday=a.get(Calendar.DAY_OF_WEEK)-1;
      int i;
      for(i=0;i<weekday;i++)s[i]=" ";
      int n=1;
      for(;i<weekday+day;i++,n++)s[i]=String.valueOf(n);
      for(;i<42;i++)s[i]=" ";
      return s;
   }
   String[] getCalendar2(){
      String s[]=new String[42];
      Calendar a=Calendar.getInstance();
      a.set(year,month-1,1);
      int weekday;
      if(a.get(Calendar.DAY_OF_WEEK)==1)weekday=6;
      else weekday=a.get(Calendar.DAY_OF_WEEK)-2;
      int i;
      for(i=0;i<weekday;i++)s[i]=" ";
      int n=1;
      for(;i<weekday+day;i++){
         s[i]=String.valueOf(n);
         n++;
      }
      for(;i<42;i++)s[i]=" ";
      return s;
   }
}