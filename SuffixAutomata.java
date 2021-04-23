import java.io.*;
import java.math.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;


public class Main {
    private static class SuffixTree {

        protected int size;
        private Node ending;
        private final Node root;

        public SuffixTree() {
            size = 0;
            root = new Node(0, null);
            ending = root;
        }

        private void addChar(char cur) {
            Node vertex = new Node(ending.len + 1, null);
            Node current = ending;
            while(current != null && !current.mp.containsKey(cur)) {
                current.mp.put(cur, vertex);
                current = current.link;
            }

            if (current == null) {
                vertex.link = root;
                ending = vertex;
                return;
            }

            Node toCurrent = current.mp.get(cur);
            if (toCurrent.len - 1 == current.len) {
                vertex.link = toCurrent;
                ending = vertex;
                return;
            }

            Node copyCurrent = new Node(current.len + 1, toCurrent.link);
            copyCurrent.mp.putAll(toCurrent.mp);
            int cou = 0;
            while (current != null && current.mp.containsKey(cur) && current.mp.get(cur) == toCurrent) {
                current.mp.put(cur, copyCurrent);
                cou += copyCurrent.mp.size();
                current = current.link;
            }
            toCurrent.link = copyCurrent;
            vertex.link = copyCurrent;
            ending = vertex;
        }


        public void addString(String s) {
            for (int i = 0; i < s.length(); ++i) {
                addChar(s.charAt(i));
                //System.out.println(ans);
            }
        }

        public class Node {
            public Node(int len, Node link) {
                this.len = len;
                this.link = link;
                size++;
                num = size;
            }
            int len;
            Node link;
            int num;
            Map<Character, Node> mp = new HashMap<>();
        }

        public Node getRoot() {
            return root;
        }

        private void dfsTree(Node node, Map<Node, Long> d, Node parent, Character c) {
            d.put(node, d.getOrDefault(node, 1L));
            for (Map.Entry<Character, Node> cur : node.mp.entrySet()) {
                if (!d.containsKey(cur.getValue())) {
                    dfsTree(cur.getValue(), d, node, cur.getKey());
                }
                d.put(node, d.get(node) + d.get(cur.getValue()));
            }
        }

        public long getDifferentStr() {
            Map<Node, Long> mp = new HashMap<>();
            dfsTree(root, mp, null, null);
            return mp.get(root) - 1L;
        }

    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        SuffixTree suffixTree = new SuffixTree();
        suffixTree.addString(s);
        System.out.println(suffixTree.getDifferentStr());
        br.close();
    }

}