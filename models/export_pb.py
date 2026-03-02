import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

meta_path = "model-145000.meta"
ckpt_path = "model-145000"

print("Loading graph (clearing device assignments)...")

saver = tf.train.import_meta_graph(meta_path, clear_devices=True)

config = tf.ConfigProto(device_count={'GPU': 0})

with tf.Session(config=config) as sess:
    print("Restoring checkpoint...")
    saver.restore(sess, ckpt_path)

    print("Exporting graph...")
    tf.train.write_graph(sess.graph_def, ".", "model-145000.pb", as_text=False)

print("Done.")
