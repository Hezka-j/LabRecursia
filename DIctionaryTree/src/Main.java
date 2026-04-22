import java.io.*;
import java.nio.file.Path;
import java.util.*;

class DictionaryTree {
    private class Node {
        public String value = "";
        public String translate_value = "";
        public Node left = null;
        public Node right = null;
        public Node parent = null;

        public Node(String value, String translate_value) {
            this.value = value;
            this.translate_value = translate_value;
        }

        public Node() {
            this("", "");
        }
    }

    private Node root = null;

    private Node Add(Node root, String value, String translation, Node parent) {
        if(root == null) {
            root = new Node(value, translation);
            root.parent = parent;
            return root;
        }
        else
        {
            int comp = root.value.compareTo(value);
            if(comp > 1) {
                root.right = Add(root.right, value, translation, root);
            }
            else {
                root.left = Add(root.left, value, translation, root);
            }
        }
        return root; //unchanged root
    }

    private Node Delete(Node root, String value) {
        if(root == null)
            return null;
        if(root.value == value)
        {
            if(root.right != null && root.left != null) {
                Node node = root.right;
                while(node != null) node = node.right;
                root = node;
            }
            else {
                Node child = root.left != null ? root.left : root.right;

                if(child != null) {
                    child.parent = root.parent;
                }
                root = child;
            }
        }
        else if(root.value.length() < value.length()) {
            root.right = Delete(root.right, value);
        }
        else {
            root.left = Delete(root.left, value);
        }
        return root;
    }

    private void Print(Node root) {
        if(root == null)
            return;
        Print(root.left);
        System.out.println(root.value + " " + root.translate_value);
        Print(root.right);
    }

    private String SearchOrig(Node root, String word) {
        if(root == null)
            return word;
        int cmp = root.value.compareTo(word);
        if(cmp == 0)
            return root.translate_value;
        if(cmp < 0)
            return SearchOrig(root.left, word);
        else
            return SearchOrig(root.right, word);
        //return null;
    }

    public void Add(String value, String translation) {
        root = Add(root, value, translation, null);
    }

    public void Delete(String value) {
        root = Delete(root, value);
    }

    public void Print() {
        Print(root);
    }

    public String Search(String word) {
        return SearchOrig(root, word);
    }
//Створити словник – текстовий файл, кожний рядок якого містить слово та його переклад.
//Заповнити бінарне дерево словами із словника.
//Ввести рядок. За допомогою дерева знайти переклад кожного слова і вивести переклад рядка на екран.
    public void Exercise(String original_file, String translate_file, String file) throws IOException {
        Scanner or = new Scanner(Path.of(original_file));
        Scanner transl = new Scanner(Path.of(translate_file));
        LinkedList<String> original = new LinkedList<>();
        LinkedList<String> translate = new LinkedList<>();
        while(or.hasNext())
            original.add(or.next());
        while(transl.hasNext())
            translate.add(transl.next());
        int i = 0;

        while(i < original.size() && i < translate.size()) {
            this.Add(original.get(i), translate.get(i));
            i++;
        }
        or = new Scanner(Path.of(file));
        while (or.hasNext()) {
            String word = or.next();
            String translated = this.Search(word);
            if (translated != null)
                System.out.print(translated + " ");
            else
                System.out.print(word + " ");
        }
    }

    public void EnterToFile(String original_file, String translate_file, String file) throws IOException{
        FileWriter orig_file = new FileWriter(original_file);
        FileWriter tran_file = new FileWriter(translate_file);
        LinkedList<String> original = new LinkedList<>();
        LinkedList<String> translate = new LinkedList<>();
        System.out.println("Enter words");
        Scanner input = new Scanner(System.in);
        while(input.hasNext()) {
            String word = input.next();
            if(word.equalsIgnoreCase("stop")) break;
            orig_file.write(word + "\n");
            original.add(word);
        }
        System.out.println("Enter translate");
        while(input.hasNext()) {
            String word = input.next();
            if(word.equalsIgnoreCase("стоп") || word.equalsIgnoreCase("stop")) break;
            tran_file.write(word + "\n");
            translate.add(word);
        }
        int i = 0;
        while(i < original.size() && i < translate.size()) {
            this.Add(original.get(i), translate.get(i));
            i++;
        }
        System.out.println("Enter line to translate");
        input.nextLine();
        String line = input.nextLine();
        Translation(line);
        orig_file.close();
        tran_file.close();
    }

    public void Translation(String line) {
        String[] words = line.split(" ");
        for(var word : words)
        {
            System.out.print(Search(word) + " ");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        try {
            String original = "original.txt";
            String translation = "translation.txt";
            String example = "file.txt";
            DictionaryTree tree = new DictionaryTree();
            tree.EnterToFile(original, translation, example);
            //tree.Exercise(original, translation, example);
        }
        catch(IOException e) {
            System.out.println("error I/O");
        }
    }
}