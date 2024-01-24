#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int
main (int argc, char *argv[])
{
  GMainLoop *loop;
  GstRTSPServer *server;
  GstRTSPMountPoints *mounts;
  GstRTSPMediaFactory *factory;

  gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);

  server = gst_rtsp_server_new ();
  mounts = gst_rtsp_server_get_mount_points (server);

  factory = gst_rtsp_media_factory_new ();

  gst_rtsp_media_factory_set_launch (factory,
    "(v4l2src device=/dev/video0 ! mpph264enc ! rtph264pay name=pay0 pt=96 zero-latency)"
  );

  gst_rtsp_mount_points_add_factory (mounts, "/stream", factory);
  g_object_unref (mounts);
  gst_rtsp_server_attach (server, NULL);

  g_print ("rtsp://172.168.0.5:8554/stream is live\n");
  g_main_loop_run (loop);

  return 0;
};

//server launch with avdec_h264
//sudo env LD_PRELOAD=/lib/aarch64-linux-gnu/libgomp.so.1 /home/rock/rtsp_server/build/rtsp_server

// client
// gst-launch-1.0 rtspsrc location=rtsp://172.168.0.5:8554/stream latency=50