from gi.repository import Gtk

class SimilarityWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Select Similarity Measures")
		self.selection_list = []

		# Containers
		self.set_default_size(300, 200)
		self.box = Gtk.VBox()
		self.bbox = Gtk.HButtonBox(spacing=6)
		self.bbox.set_layout(Gtk.ButtonBoxStyle.START)

		# List model
		self.store = Gtk.ListStore(str)
		self.store.append(["Euclidean Distance"])
		self.store.append(["Pearson Correlation"])

		# List view
		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Similarity Index", self.renderer, text=0)
		self.treeview.append_column(self.column)
		self.box.pack_start(self.treeview, True, True, 0)

		# List control
		self.selection = self.treeview.get_selection()
		self.selection.set_mode(Gtk.SelectionMode.MULTIPLE)
		self.selection.connect("changed", self.on_tree_selection_changed)

		# Control buttons
		self.button_ok = Gtk.Button(stock=Gtk.STOCK_OK)
		self.button_cancel = Gtk.Button(stock=Gtk.STOCK_CANCEL)
		self.button_ok.connect("clicked", self.on_button_ok_clicked)
		self.button_cancel.connect("clicked", self.on_button_cancel_clicked)

		# Packing buttons
		self.bbox.pack_start(self.button_ok, True, True, 0)
		self.bbox.pack_start(self.button_cancel, True, True, 0)
		self.box.pack_start(self.bbox, True, True, 0)
		self.add(self.box)

	def on_tree_selection_changed(self, widget):
		self.model, self.treeiter = self.selection.get_selected_rows()

	def on_button_ok_clicked(self, widget):
		self.model, self.treeiter = self.selection.get_selected_rows()
		for row in self.treeiter:
			self.selection_list.append(self.model[row][0])
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.hide()

	def get_selection_list(self):
		return self.selection_list
