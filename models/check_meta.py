import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

tf.reset_default_graph()

saver = tf.train.import_meta_graph(
    "model-145000.meta",
    clear_devices=True
)

graph = tf.get_default_graph()

for v in tf.global_variables():
    print(v.name)
