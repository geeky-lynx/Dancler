#include <stdio.h>
#include <gtk/gtk.h>

char count = 0;

gboolean hello(GtkWidget *widget, GdkEvent *event, gpointer data) {
  printf("pointer in hello(): %p\n", data);
  printf("data value: %d\n", *(int*)data);
}

gboolean goodbye(GtkWidget *shit) {
    printf("goodbye: %p\n", shit);
    gtk_label_set_text(GTK_LABEL(shit), "123");
    return true;
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *box;
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *anotherBtn;
  GtkWidget *label;


  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  button = gtk_button_new_with_label("Hello World");
  anotherBtn = gtk_button_new_with_label("Bye World");
  label = gtk_label_new("errmmmmm");

  // printf("pointer in activate(): %p\n", ptr);
  // printf("abc value: %d\n", *(int*)ptr);
  // Problem occurs here.
  printf("activate: %p\n", label);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), user_data);
  g_signal_connect_swapped(G_OBJECT(anotherBtn), "clicked", G_CALLBACK(goodbye), label);
  // gtk_window_set_child(GTK_WINDOW(window), button);
  gtk_box_append(GTK_BOX(box), label);
  gtk_box_append(GTK_BOX(box), anotherBtn);
  gtk_window_set_child(GTK_WINDOW(window), box);

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
