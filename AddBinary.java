public class AddBinary {
    public static void main(String[] args) {
        String a = "101", b = "10";
        StringBuilder arev = new StringBuilder(a).reverse();
        StringBuilder brev = new StringBuilder(b).reverse();

        Integer abase10 = 0, bbase10 = 0;

        for (int i = 0; i < arev.length(); i++) {
            abase10 += arev.charAt(i) == '1' ? (1 << i) : 0;
        }

        for (int i = 0; i < brev.length(); i++) {
            bbase10 += brev.charAt(i) == '1' ? (1 << i) : 0;
        }

        System.out.println(abase10);
        System.out.println(bbase10);

        Integer sum = abase10 + bbase10;
        String sumBinary = Integer.toBinaryString(sum);
        System.out.println(sumBinary);
    }
}
