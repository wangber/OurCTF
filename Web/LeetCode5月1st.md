# LeetCode 5月第一期

## 1 两数和

```java
class Solution {
    public static void main(String[] args){

    }
    public int[] twoSum(int[] nums, int target) {
        int[] a=new int[2];
        int k=0;

           outer: for (int i = 0; i < nums.length; i++) {
                for (int j = i+1; j < nums.length; j++) {
                    if (nums[i] + nums[j] == target) {
//避免使用到同一个位置的数，j=j+1
                        a[0] = i;
                        a[1] = j;
                        k = k + 1;
                        break outer; //掌握跳出大循环的方法
                    } else {
                        continue;
                    }

                }
            }

            return a;
    }
}
```

## 整数反转

测试代码：

```java
class Solution {
    public static void main(String[] args) {
        Solution a=new Solution();
        System.out.println(a.reverse(1534236469));
    }
    public int reverse(int x){
        long rev=0;  //防止反转后超出int范围
        int p=0;
        while(x!=0) {
            p = x % 10;  //通过取模方法获取最后一位数
            rev = rev * 10 + p; //每次将前面取出来的数乘以10，再加上新的个位数
            if (rev < Integer.MIN_VALUE || rev > Integer.MAX_VALUE) {   //注意溢出检测
                return 0;
            }
            x = x / 10;
        }
        return (int)rev; //再转换为int
        }
    }

```

## 回文数

将整数的一半反转，然后与未反转的另一半做比较。当反转后的数大于未反转后的数时，反转结束。

特殊情况：

小于10以及10的倍数：直接返回false

0：true

奇数：反转后的数再/10，直接忽略掉中间的那一位

测试代码：

```java
class Solution {
    public static void main(String[] args){
        Solution a=new Solution();
        System.out.println(a.re(10));
    }
    public boolean re(int x){
        int renum=0;
        //特殊情况的处理
        if (x<0 || (x%10==0 && x!=0)){
            return false;
        }
        else{
            if (x==0){
                return true;
            }
            else{
                while(x>renum) {
                    int last;
                    last = x % 10;
                    renum = renum * 10 + last;
                    x = x / 10;
                }
            }
        }
        return x==renum || x==renum/10;
    }
}
```



