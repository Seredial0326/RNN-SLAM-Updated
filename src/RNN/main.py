import sys
print(sys.version)

sys.path.append('/home/egistp/Desktop/RNN-SLAM/src/RNN')
import RNN_pred_colon_reproj
net = RNN_pred_colon_reproj.RNN_depth_pred('/home/egistp/RNN-SLAM/models/model-145000', output_dir='/home/egistp/Desktop/')



net.assign_keyframe_by_path('/home/egistp/Desktop/prueba.jpg')
net.predict('/home/egistp/Desktop/prueba.jpg')
net.update()