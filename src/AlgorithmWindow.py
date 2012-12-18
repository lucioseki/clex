from gi.repository import Gtk

class AlgorithmWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Set Algorithm Proprieties")
		
		self.call_string = "clustering/cluster"

		self.set_default_size(300, 200)
		self.box = Gtk.VBox()
		self.bbox = Gtk.HButtonBox(spacing=6)
		self.bbox.set_layout(Gtk.ButtonBoxStyle.START)

		self.store = Gtk.ListStore(str)
		self.store.append(["K-means"])
		self.store.append(["Pairwise complete-linkage"])
		self.store.append(["Pairwise single-linkage"])
		self.store.append(["Pairwise centroid-linkage"])
		self.store.append(["Pairwise average-linkage"])

		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Algorithm", self.renderer, text=0)
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
		self.algorithm = self.model[self.treeiter][0]
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.hide()

	def get_call_string(self):
		return self.call_string
	
	def get_params(self):
		return "" 
