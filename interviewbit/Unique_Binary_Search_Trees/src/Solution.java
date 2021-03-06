import java.util.*;
import java.util.stream.IntStream;

public class Solution {
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        List<TreeNode> trees = s.generateTrees(Integer.parseInt(args[0]));
        System.out.println(trees.size());
    }

    enum Dir {LEFT, RIGHT}

    static class EdgeDesc {
        int src;
        Dir dir;
        int dst;

        EdgeDesc(int src, Dir dir, int dst) {
            this.src = src;
            this.dir = dir;
            this.dst = dst;
        }
    }

    static class TreeDesc {
        int root;
        Set<Integer> vertices;
        List<EdgeDesc> edges;

        TreeDesc(int root, Set<Integer> vertices, List<EdgeDesc> edges) {
            this.root = root;
            this.vertices = vertices;
            this.edges = edges;
        }

        static TreeDesc of(int root) {
            return join(root, null, null);
        }

        static TreeDesc join(int root, TreeDesc tdLeft, TreeDesc tdRight) {
            Set<Integer> vertices = new HashSet<>();
            vertices.add(root);
            List<EdgeDesc> edges = new LinkedList<>();

            if (tdLeft != null) {
                vertices.addAll(tdLeft.vertices);
                edges.add(new EdgeDesc(root, Dir.LEFT, tdLeft.root));
                edges.addAll(tdLeft.edges);
            }

            if (tdRight != null) {
                vertices.addAll(tdRight.vertices);
                edges.add(new EdgeDesc(root, Dir.RIGHT, tdRight.root));
                edges.addAll(tdRight.edges);
            }

            return new TreeDesc(root, vertices, edges);
        }
    }

    public ArrayList<TreeNode> generateTrees(int a) {
        int[] vertices = IntStream.rangeClosed(1, a).toArray();
        List<TreeDesc> treeDescs = gen(vertices);

        ArrayList<TreeNode> result = new ArrayList<>();

        for (TreeDesc td : treeDescs) {
            result.add(tree(td));
        }

        return result;
    }

    private static List<TreeDesc> gen(int[] vertices) {
        if (vertices.length == 0) return listOf();
        if (vertices.length == 1) return listOf(TreeDesc.of(vertices[0]));

        List<TreeDesc> result = new LinkedList<>();

        for (int i = 0; i < vertices.length; ++i) {
            int root = vertices[i];
            int[] leftVertices = Arrays.copyOfRange(vertices, 0, i);
            int[] rightVertices = Arrays.copyOfRange(vertices, i + 1, vertices.length);

            List<TreeDesc> leftTrees = gen(leftVertices);
            List<TreeDesc> rightTrees = gen(rightVertices);

            if (leftTrees.size() == 0) {
                for (TreeDesc r : rightTrees) {
                    result.add(TreeDesc.join(root, null, r));
                }
                continue;
            }

            if (rightTrees.size() == 0) {
                for (TreeDesc l : leftTrees) {
                    result.add(TreeDesc.join(root, l, null));
                }
                continue;
            }

            for (TreeDesc l : leftTrees) {
                for (TreeDesc r: rightTrees) {
                    result.add(TreeDesc.join(root, l, r));
                }
            }
        }

        return result;
    }

    private static TreeNode tree(TreeDesc desc) {
        Map<Integer, TreeNode> nodes = new HashMap<>();

        for (int v : desc.vertices) {
            nodes.put(v, new TreeNode(v));
        }

        for (EdgeDesc e : desc.edges) {
            TreeNode srcNode = nodes.get(e.src);
            TreeNode dstNode = nodes.get(e.dst);

            if (e.dir == Dir.LEFT) {
                srcNode.left = dstNode;
            } else {
                srcNode.right = dstNode;
            }
        }

        return nodes.get(desc.root);
    }

    private static List<TreeDesc> listOf() {
        return new LinkedList<>();
    }

    private static List<TreeDesc> listOf(TreeDesc td) {
        List<TreeDesc> result = new LinkedList<>();
        result.add(td);
        return result;
    }
}
