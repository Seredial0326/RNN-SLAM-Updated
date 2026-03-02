import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

from tensorflow.python.platform import gfile

with tf.Graph().as_default():
    graph_def = tf.GraphDef()
    with gfile.GFile("model-145000.pb", "rb") as f:
        graph_def.ParseFromString(f.read())
        tf.import_graph_def(graph_def, name="")

    graph = tf.get_default_graph()

    with open("graph_ops.txt", "w") as out:
        for op in graph.get_operations():
            out.write(op.name + "\n")

print("Saved to graph_ops.txt")
