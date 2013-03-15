from gi.repository import Gtk

class AlgorithmWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title="Set Algorithms")
		self.algorithm_param_list = []

		# clustering program path
		self.clustering_program_path = "clustering/cluster"

		# Containers
		self.set_default_size(300, 200)
		self.box = Gtk.VBox()
		self.bbox = Gtk.HButtonBox(spacing=6)
		self.bbox.set_layout(Gtk.ButtonBoxStyle.START)
		self.parambox = Gtk.VBox(spacing=6)
		self.hbox_minK = Gtk.HBox(spacing=6)
		self.hbox_maxK = Gtk.HBox(spacing=6)
		self.hbox_exec_times = Gtk.HBox(spacing=6)

		# Algorithm List
		# List model
		self.store = Gtk.ListStore(str)
		self.store.append(["K-means"])
		self.store.append(["Pairwise complete-linkage"])
		self.store.append(["Pairwise single-linkage"])
		self.store.append(["Pairwise centroid-linkage"])
		self.store.append(["Pairwise average-linkage"])

		# List view
		self.treeview = Gtk.TreeView(self.store)
		self.renderer = Gtk.CellRendererText()
		self.column = Gtk.TreeViewColumn("Algorithm", self.renderer, text=0)
		self.treeview.append_column(self.column)

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

		# Algorithm parameters
		self.label_min_cluster = Gtk.Label("Min. Cluster number: ")
		self.spin_min_cluster = Gtk.SpinButton()
		self.spin_min_cluster.set_adjustment(Gtk.Adjustment(2, 2, 100, 1, 10, 0))
		self.spin_min_cluster.set_numeric(True)

		self.label_max_cluster = Gtk.Label("Max. Cluster number: ")
		self.spin_max_cluster = Gtk.SpinButton()
		self.spin_max_cluster.set_adjustment(Gtk.Adjustment(2, 2, 100, 1, 10, 0))
		self.spin_max_cluster.set_numeric(True)

		self.label_times = Gtk.Label("Times to execute\n non-deterministic\n algorithms: ")
		self.spin_times = Gtk.SpinButton()
		self.spin_times.set_adjustment(Gtk.Adjustment(1, 1, 100, 1, 10, 0))
		self.spin_times.set_numeric(True)
		self.hbox_exec_times.pack_start(self.label_times, True, True, 0)
		self.hbox_exec_times.pack_start(self.spin_times, True, True, 0)

		self.hbox_minK.pack_start(self.label_min_cluster, True, True, 0)
		self.hbox_minK.pack_start(self.spin_min_cluster, True, True, 0)
		self.hbox_maxK.pack_start(self.label_max_cluster, True, True, 0)
		self.hbox_maxK.pack_start(self.spin_max_cluster, True, True, 0)

		self.parambox.pack_start(self.hbox_minK, True, True, 0)
		self.parambox.pack_start(self.hbox_maxK, True, True, 0)
		self.parambox.pack_start(self.hbox_exec_times, True, True, 0)

		# Packing into window
		self.box.pack_start(self.treeview, True, True, 0)
		self.box.pack_start(self.parambox, True, True, 0)
		self.box.pack_start(self.bbox, True, True, 0)
		self.add(self.box)

	def on_tree_selection_changed(self, widget):
		self.model, self.treeiter = self.selection.get_selected_rows()

	def on_button_ok_clicked(self, widget):
		self.model, self.treeiter = self.selection.get_selected_rows()

		for row in self.treeiter:
			self.alg = self.model[row][0]
			if(self.alg == "K-means"):
				self.param = "k"
			elif(self.alg == "Pairwise complete-linkage"):
				self.param = "m"
			elif(self.alg == "Pairwise single-linkage"):
				self.param = "s"
			elif(self.alg == "Pairwise centroid-linkage"):
				self.param = "c"
			elif(self.alg == "Pairwise average-linkage"):
				self.param = "a"

			self.algorithm_param_list.append(self.param)
		self.hide()

	def on_button_cancel_clicked(self, widget):
		self.hide()

	def get_algorithm_param_list(self):
		return self.algorithm_param_list

	def get_clustering_program_path(self):
		return self.clustering_program_path
	
	def get_minK(self):
		return self.spin_min_cluster.get_value_as_int()

	def get_maxK(self):
		return self.spin_max_cluster.get_value_as_int()

	def get_execution_times(self):
		return self.spin_times.get_value_as_int()
