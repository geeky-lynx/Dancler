#include "./interface-api.h"

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

static GArray *songs;

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
static void play_from_playlist(const GtkTreeView *tree);



void create_playlist_ui(GtkWidget *windowBox) {
    GtkWidget   *playlistBox = NULL,

                *scrollableArea = NULL,
                *playlistTable = NULL,

                *actionBox = NULL,
                *findButton = NULL;

    GtkTreeModel *itemsModel = NULL;

    songs = g_array_sized_new(false, false, sizeof(Item), 1);


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
    auto selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(playlistTable));
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollableArea), playlistTable);
    g_signal_connect_swapped(G_OBJECT(playlistTable), "row-activated", G_CALLBACK(play_from_playlist), playlistTable);

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






static void play_from_playlist(const GtkTreeView *tree) {
    printf("\nligma burek\n");
    GtkTreeIter iter;
    GtkTreeView *treeView = tree;
    GtkTreeModel *model = gtk_tree_view_get_model(treeView);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeView);
    auto row = gtk_tree_selection_get_selected(selection, NULL, &iter);

    if (row) {
        int i;
        GtkTreePath *path;
        path = gtk_tree_model_get_path(model, &iter);
        i = gtk_tree_path_get_indices(path)[0];
        Item tmp = g_array_index(songs, Item, i);
        printf("%d - %s - %s\n", tmp.num, tmp.filepath, tmp.title);

    }
    else {
        printf("eeerm what the fuck?\n");
    }
}
