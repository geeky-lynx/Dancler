#include "../header.h"
#include "./gui-controls.h"

#define DEFAULT_COVER_IMAGE_ "assets/no-cover.png"
#define DEFAULT_TITLE_NO_PLAYBACK_ "No playback"
#define DEFAULT_TITLE_NO_TITLE_ "Unknown title"
#define DEFAULT_AUTHORS_ "Unknown authors"
#define DEFAULT_ZERO_TIMER_ "0:00"

static GtkAdjustment *playbackTime; // To be used for time slider
static GtkAdjustment *playbackVolume; // To be used for volume slider
static GArray *songs;

static void initialize_ui_values(); // Initialized all required values
static void create_playback_ui(GtkWidget *windowBox); // Forms information & controls for current playback
static void create_playlist_ui(GtkWidget *windowBox); // Forms playlist table (list of songs)

G_GNUC_BEGIN_IGNORE_DEPRECATIONS


typedef struct _Item {
    int num;
    char *filepath;
    char *title;
} Item;

enum {
    COLUMN_ITEM_NUM,
    COLUMN_ITEM_FILEPATH,
    COLUMN_ITEM_TITLE,

    NUM_ITEM_COLUMNS
};

enum {
    COLUMN_NUMBER_TEXT,
    NUM_NUMBER_COLUMNS
};

static void add_items();
static GtkTreeModel *create_items_model();
static gboolean separator_row(GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
static void add_columns(GtkTreeView *treeView, GtkTreeModel *items_model);


void initialize_window_layout(GtkApplication *application, gpointer userData) {
    GtkWidget   *mainWindow = NULL,
                *mainBox = NULL;

    initialize_ui_values();

    /* Creating base for main window */
    mainWindow = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Dancler");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 600, 400);

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(mainWindow), mainBox);

    create_playback_ui(mainBox);
    create_playlist_ui(mainBox);

    gtk_window_present(GTK_WINDOW(mainWindow));
}



static void initialize_ui_values() {
    playbackTime = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 1.0, 1.0);
    playbackVolume = gtk_adjustment_new(100.0, 0.0, 100.0, 1.0, 1.0, 1.0);
    songs = g_array_sized_new(false, false, sizeof(Item), 1);
}



static void create_playback_ui(GtkWidget *windowBox) {
    GtkWidget   *playbackBox = NULL,

                *infoAndControlBox = NULL,
                *infoBox = NULL,
                *titleLabel = NULL,
                *authorsLabel = NULL,
                *coverBox = NULL,
                *coverImage = NULL,

                *controlsBox = NULL,
                *timeBox = NULL,
                *currentTimeLabel = NULL,
                *totalTimeLabel = NULL,
                *timeSlider = NULL,

                *actionsBox = NULL,
                *playStopButton = NULL,
                *nextButton = NULL,
                *previousButton = NULL,
                *muteButton = NULL,
                *volumeSlider = NULL;


    playbackBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(playbackBox, GTK_ALIGN_START);
    gtk_widget_set_valign(playbackBox, GTK_ALIGN_START);


    /* Creating audio cover GUI elements */
    coverBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(coverBox, GTK_ALIGN_START);
    gtk_widget_set_valign(coverBox, GTK_ALIGN_START);

    coverImage = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(coverImage), DEFAULT_COVER_IMAGE_);
    gtk_widget_set_size_request(GTK_WIDGET(coverImage), 200, 200);


    /* Creating audio playback information GUI elements (duh) */
    infoAndControlBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoAndControlBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoAndControlBox, GTK_ALIGN_START);

    infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoBox, GTK_ALIGN_START);

    titleLabel = gtk_label_new(DEFAULT_TITLE_NO_PLAYBACK_);
    // gtk_widget_set_hexpand(GTK_WIDGET(titleLabel), true);
    // gtk_label_set_font_size(GTK_LABEL(titleLabel), 18.0); // method doesn't exist
    authorsLabel = gtk_label_new(DEFAULT_AUTHORS_);
    gtk_widget_set_hexpand(GTK_WIDGET(authorsLabel), true);


    /* Creating time stuff GUI elements */
    controlsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(controlsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(controlsBox, GTK_ALIGN_START);

    timeBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(timeBox, GTK_ALIGN_START);
    gtk_widget_set_valign(timeBox, GTK_ALIGN_START);
    gtk_widget_set_hexpand(timeBox, true);

    currentTimeLabel = gtk_label_new(DEFAULT_ZERO_TIMER_);
    totalTimeLabel = gtk_label_new(DEFAULT_ZERO_TIMER_);
    timeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, playbackTime);
    gtk_widget_set_size_request(timeSlider, 500, -1);


    /* Creating playback control GUI elements */
    actionsBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(actionsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(actionsBox, GTK_ALIGN_START);


    playStopButton = gtk_button_new_from_icon_name("media-playback-start"); // or "dancler-play-stop"
    previousButton = gtk_button_new_from_icon_name("media-skip-backward"); // or "dancler-previous"
    nextButton = gtk_button_new_from_icon_name("media-skip-forward"); // or "dancler-next"
    muteButton = gtk_button_new_from_icon_name("audio-volume-muted"); // or "dancler-mute"
    volumeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, playbackVolume);
    gtk_widget_set_size_request(volumeSlider, 150, -1);
    g_signal_connect_swapped(G_OBJECT(playStopButton), "clicked", G_CALLBACK(play_stop_current_audio), titleLabel);
    g_signal_connect_swapped(G_OBJECT(previousButton), "clicked", G_CALLBACK(start_previous_audio), titleLabel);
    g_signal_connect_swapped(G_OBJECT(nextButton), "clicked", G_CALLBACK(start_next_audio), titleLabel);
    g_signal_connect_swapped(G_OBJECT(muteButton), "clicked", G_CALLBACK(mute_audio), NULL);
    g_signal_connect_swapped(G_OBJECT(volumeSlider), "value-changed", G_CALLBACK(change_volume), playbackVolume);


    /* Put everything on the window */
    gtk_box_append(GTK_BOX(coverBox), coverImage);
    gtk_box_append(GTK_BOX(playbackBox), coverBox);

    gtk_box_append(GTK_BOX(infoBox), titleLabel);
    gtk_box_append(GTK_BOX(infoBox), authorsLabel);

    gtk_box_append(GTK_BOX(infoAndControlBox), infoBox);

    gtk_box_append(GTK_BOX(timeBox), currentTimeLabel);
    gtk_box_append(GTK_BOX(timeBox), timeSlider);
    gtk_box_append(GTK_BOX(timeBox), totalTimeLabel);

    gtk_box_append(GTK_BOX(controlsBox), timeBox);

    gtk_box_append(GTK_BOX(actionsBox), previousButton);
    gtk_box_append(GTK_BOX(actionsBox), playStopButton);
    gtk_box_append(GTK_BOX(actionsBox), nextButton);
    gtk_box_append(GTK_BOX(actionsBox), muteButton);
    gtk_box_append(GTK_BOX(actionsBox), volumeSlider);

    gtk_box_append(GTK_BOX(controlsBox), actionsBox);

    gtk_box_append(GTK_BOX(infoAndControlBox), controlsBox);

    gtk_box_append(GTK_BOX(playbackBox), infoAndControlBox);

    gtk_box_append(GTK_BOX(windowBox), playbackBox);
}



static void create_playlist_ui(GtkWidget *windowBox) {
    GtkWidget   *playlistBox = NULL,

                *scrollableArea = NULL,
                *playlistTable = NULL,

                *actionBox = NULL,
                *findButton = NULL;

    GtkTreeModel *itemsModel = NULL;

    playlistBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Creating a space for scrolling
    scrollableArea = gtk_scrolled_window_new();
    gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(scrollableArea), true);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableArea),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC
    );

    /* Forming playlist table (with deprecated TreeView) */
    itemsModel = create_items_model();
    playlistTable = gtk_tree_view_new_with_model(itemsModel);
    gtk_widget_set_vexpand(playlistTable, true);
    auto tmp = gtk_tree_view_get_selection(GTK_TREE_VIEW(playlistTable));
    gtk_tree_selection_set_mode(tmp, GTK_SELECTION_SINGLE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollableArea), playlistTable);

    add_columns(GTK_TREE_VIEW(playlistTable), itemsModel);

    g_object_unref(itemsModel);


    actionBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    findButton = gtk_button_new_from_icon_name("edit-find");
    gtk_box_append(GTK_BOX(actionBox), findButton);


    /* Putting everything on window */
    gtk_box_append(GTK_BOX(playlistBox), scrollableArea);
    gtk_box_append(GTK_BOX(playlistBox), actionBox);
    gtk_box_append(GTK_BOX(windowBox), playlistBox);
}



// Temporary shit (just to see if things work)
static void add_items() {
    Item tmp;
    g_return_if_fail(songs != NULL);

    tmp.num = 1;
    tmp.filepath = g_strdup("FH.mp3");
    tmp.title = g_strdup("Fearless Hero");
    g_array_append_vals(songs, &tmp, 1);

    tmp.num = 2;
    tmp.filepath = g_strdup("ShesHomeless.mp3");
    tmp.title = g_strdup("She\'s Homeless");
    g_array_append_vals(songs, &tmp, 1);

    tmp.num = 3;
    tmp.filepath = g_strdup("BG-HS.mp3");
    tmp.title = g_strdup("Barbie Girl (Hardstyle)");
    g_array_append_vals(songs, &tmp, 1);
}

static GtkTreeModel* create_items_model() {
    unsigned int i = 0;
    GtkListStore *model;
    GtkTreeIter iter;

    add_items();

    model = gtk_list_store_new(NUM_ITEM_COLUMNS,
        G_TYPE_INT,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_BOOLEAN
    );

    for (i = 0; i < songs->len; i++) {
        gtk_list_store_append(model, &iter);
        gtk_list_store_set(model, &iter,
            COLUMN_ITEM_NUM, g_array_index(songs, Item, i).num,
            COLUMN_ITEM_FILEPATH, g_array_index(songs, Item, i).filepath,
            COLUMN_ITEM_TITLE, g_array_index(songs, Item, i).title,
            -1
        );
    }

    return GTK_TREE_MODEL(model);
}

static gboolean separator_row(GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    GtkTreePath *path;
    int index;

    path = gtk_tree_model_get_path(model, iter);
    index = gtk_tree_path_get_indices(path)[0];
    gtk_tree_path_free(path);
    return index == 5;
}

static void add_columns(GtkTreeView *treeView, GtkTreeModel *items_model) {
    GtkCellRenderer *renderer;
    // Number column
    renderer = gtk_cell_renderer_combo_new();
    g_object_set(renderer,
        // "model", numbers_model
        // "text-column", COLUMN_NUMBER_TEXT,
        // "has-entry", FALSE,
        "editable", FALSE,
        NULL
    );

    g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ITEM_NUM));
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeView),
        -1, "Number", renderer,
        "text", COLUMN_ITEM_NUM,
        NULL
    );

    // Filepath column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer,
        "editable", FALSE,
        NULL
    );

    g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ITEM_FILEPATH));
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeView),
        -1, "Filepath", renderer,
        "text", COLUMN_ITEM_FILEPATH,
        NULL
    );

    // Title column
    renderer = gtk_cell_renderer_text_new();

    g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ITEM_TITLE));
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeView),
        -1, "Title", renderer,
        "text", COLUMN_ITEM_TITLE,
        NULL
    );
}
