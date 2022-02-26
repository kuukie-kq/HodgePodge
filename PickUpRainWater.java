package test;

public class PickUpRainWater {
    /**
     * 42.接雨水 思路 找出所有凹槽并填充对应无凹槽数，然后相减
     */
    public static int trap(int[] height) {
        int sum = 0;
        int[] supple = supplement(leftScan(height), rightScan(height));
        for (int i=0;i<height.length;i++) {
            sum = sum + supple[i] - height[i];
        }
        return sum;
    }

    private static int[] leftScan(int[] height) {
        int[] result = new int[height.length];
        for (int i=0;i<height.length;i++) {
            if (i == 0) {
                result[i] = height[i];
                continue;
            }
            if(height[i] > result[i-1]) {
                result[i] = height[i];
            } else {
                result[i] = result[i-1];
            }
        }
        return result;
    }

    private static int[] rightScan(int[] height) {
        int[] result = new int[height.length];
        for (int i=height.length-1;i>=0;i--) {
            if (i == height.length-1) {
                result[i] = height[i];
                continue;
            }
            if(height[i] > result[i+1]) {
                result[i] = height[i];
            } else {
                result[i] = result[i+1];
            }
        }
        return result;
    }

    private static int[] supplement(int[] left, int[] right) {
        int[] result = new int[left.length];
        for (int i=0;i<left.length;i++) {
            if (left[i] > right[i]) {
                result[i] = right[i];
            } else {
                result[i] = left[i];
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[] i = new int[] {0,1,0,2,1,0,1,3,2,1,2,1};
        System.out.println(PickUpRainWater.trap(i));
    }
}
