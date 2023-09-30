#include <stdio.h>
#include <gtk/gtk.h>

gboolean hello(GtkWidget *widget, GdkEvent *event, gpointer data) {
  printf("pointer in hello(): %p\n", data);
  printf("data value: %d\n", *(int*)data);
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;

  

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  button = gtk_button_new_with_label("Hello World");

  // printf("pointer in activate(): %p\n", ptr);
  // printf("abc value: %d\n", *(int*)ptr);
  // Problem occurs here.
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), user_data);
  gtk_window_set_child(GTK_WINDOW(window), button);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  gint abc = 5;
  gpointer ptr = &abc;

  printf("pointer in activate(): %p\n", ptr);
  printf("abc value: %d\n", *(int*)ptr);

  app = gtk_application_new("org.gtk.example", G_APPLICATION_REPLACE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), ptr);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
