from gi.repository import Gtk

class SimilarityWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Select Similarity Measures")
		self.similarity = "Euclidean"

		self.set_default_size(300, 200)
		self.box = Gtk.VBox()
		self.bbox = Gtk.HButtonBox(spacing=6)
		self.bbox.set_layout(Gtk.ButtonBoxStyle.START)

		self.store = Gtk.ListStore(str)
		self.store.append(["Euclidean"])
		self.store.append(["Pearson"])

		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Similaridade", self.renderer, text=0)
		self.treeview.append_column(self.column)
		self.box.pack_start(self.treeview, True, True, 0)

		self.button_ok = Gtk.Button(stock=Gtk.STOCK_OK)
		self.button_cancel = Gtk.Button(stock=Gtk.STOCK_CANCEL)
		self.button_ok.connect("clicked", self.on_button_ok_clicked)
		self.button_cancel.connect("clicked", self.on_button_cancel_clicked)
		self.bbox.pack_start(self.button_ok, True, True, 0)
		self.bbox.pack_start(self.button_cancel, True, True, 0)
		self.box.pack_start(self.bbox, True, True, 0)
		self.add(self.box)

	def on_button_ok_clicked(self, widget):
		self.selection = self.treeview.get_selection()
		self.model, self.treeiter = self.selection.get_selected()
		self.similarity = self.model[self.treeiter][0]
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.hide()

	def get_similarity(self):
		return self.similarity
