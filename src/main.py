#!/usr/bin/env python
# main loop of the program

from gi.repository import Gtk
from DataSetWindow import *
from PartitionWindow import *
from SimilarityWindow import *
from ExternalValidationWindow import *
from InternalValidationWindow import *
from AlgorithmWindow import *
from Clex_module import *
from subprocess import call
from os import path
from urlparse import urlparse 


class RealPartitionWindow(PartitionWindow):
	def __init__(self):
		PartitionWindow.__init__(self, title="Select Real Partitions")

class GeneratedPartitionWindow(PartitionWindow):
	def __init__(self):
		PartitionWindow.__init__(self, title="Select Generated Partitions")

class MainWindow(Gtk.Window):
	def __init__(self):
		# Create a new window
		Gtk.Window.__init__(self, title="Clustering Experimenter")
		
		# Containers
		self.vbox = Gtk.VBox(spacing=6)
		self.vbox_general = Gtk.VBox(spacing=6)
		self.vbox_windows = Gtk.VBox(spacing=6)
		self.hbox = Gtk.HBox(spacing=6)

		# General Configuration Frame
		self.frame_general = Gtk.Frame(label="General Settings")
		self.hbox1 = Gtk.HBox(spacing=6)
		self.hbox2 = Gtk.HBox(spacing=6)
		self.hbox3 = Gtk.HBox(spacing=6)
		self.hbox4 = Gtk.HBox(spacing=6)
		self.hbox5 = Gtk.HBox(spacing=6)
		self.hbox6 = Gtk.HBox(spacing=6)

		# Button Boxes
		self.bbox1 = Gtk.VButtonBox(spacing=6)
		self.bbox2 = Gtk.VButtonBox(spacing=6)
		self.bbox3 = Gtk.HButtonBox(spacing=6)
		self.bbox1.set_layout(Gtk.ButtonBoxStyle.START)
		self.bbox2.set_layout(Gtk.ButtonBoxStyle.START)
		self.bbox3.set_layout(Gtk.ButtonBoxStyle.START)

		# Packing containers
		self.hbox.pack_start(self.bbox1, True, True, 0)
		self.hbox.pack_start(self.bbox2, True, True, 0)
		self.vbox_general.pack_start(self.hbox1, True, True, 0)
		self.vbox_general.pack_start(self.hbox2, True, True, 0)
		self.vbox_general.pack_start(self.hbox3, True, True, 0)
		self.vbox_general.pack_start(self.hbox4, True, True, 0)
		self.vbox_general.pack_start(self.hbox5, True, True, 0)
		self.vbox_general.pack_start(self.hbox6, True, True, 0)
		self.vbox_windows.pack_start(self.hbox, True, True, 0)
		self.vbox_windows.pack_start(self.bbox3, True, True, 0)
		self.frame_general.add(self.vbox_general)
		self.vbox.pack_start(self.frame_general, True, True, 0)
		self.vbox.pack_start(self.vbox_windows, True, True, 0)
		self.add(self.vbox)

		# General configuration
		self.label_name = Gtk.Label("Experiment name: ")
		self.entry_name = Gtk.Entry()
		self.label_dir = Gtk.Label("Directory: ")
		self.entry_dir = Gtk.Entry()
		self.label_time = Gtk.Label("Show execution time: ")
		self.check_time = Gtk.CheckButton()
		self.label_min_cluster = Gtk.Label("Min. Cluster number: ")
		self.spin_min_cluster = Gtk.SpinButton()
		self.spin_min_cluster.set_adjustment(Gtk.Adjustment(2, 2, 100, 1, 10, 0))
		self.spin_min_cluster.set_numeric(True)

		self.label_max_cluster = Gtk.Label("Max. Cluster number: ")
		self.spin_max_cluster = Gtk.SpinButton()
		self.spin_max_cluster.set_adjustment(Gtk.Adjustment(2, 2, 100, 1, 10, 0))
		self.spin_max_cluster.set_numeric(True)
		self.label_times = Gtk.Label("Times to execute: ")
		self.spin_times = Gtk.SpinButton()
		self.spin_times.set_adjustment(Gtk.Adjustment(1, 1, 100, 1, 10, 0))
		self.spin_times.set_numeric(True)

		self.hbox1.pack_start(self.label_name, True, True, 0)
		self.hbox1.pack_start(self.entry_name, True, True, 0)
		self.hbox2.pack_start(self.label_dir, True, True, 0)
		self.hbox2.pack_start(self.entry_dir, True, True, 0)
		self.hbox3.pack_start(self.label_time, True, True, 0)
		self.hbox3.pack_start(self.check_time, True, True, 0)
		self.hbox4.pack_start(self.label_min_cluster, True, True, 0)
		self.hbox4.pack_start(self.spin_min_cluster, True, True, 0)
		self.hbox5.pack_start(self.label_max_cluster, True, True, 0)
		self.hbox5.pack_start(self.spin_max_cluster, True, True, 0)
		self.hbox6.pack_start(self.label_times, True, True, 0)
		self.hbox6.pack_start(self.spin_times, True, True, 0)


		# Buttons to open other windows
		self.button_dataset = Gtk.Button(label="Load DataSets")
		self.button_real_partition = Gtk.Button(label="Load Real Partitions")
		self.button_generated_partition = Gtk.Button(label="Load Generated Partitions")
		self.button_similarity = Gtk.Button(label="Set Similarity Measure")
		self.button_external_validation = Gtk.Button(label="Set External Validation Indexes")
		self.button_internal_validation = Gtk.Button(label="Set Internal Validation Indexes")
		self.button_algorithm = Gtk.Button(label="Set Algorithms")
		self.button_execute = Gtk.Button(stock=Gtk.STOCK_EXECUTE)
		self.button_save = Gtk.Button(stock=Gtk.STOCK_SAVE)
		self.button_open = Gtk.Button(stock=Gtk.STOCK_OPEN)
		self.button_close = Gtk.Button(stock=Gtk.STOCK_CLOSE)

		# Connect the callback functions to the click event
		self.button_dataset.connect("clicked", self.on_button_dataset_clicked)
		self.button_real_partition.connect("clicked", self.on_button_real_partition_clicked, "Real")
		self.button_generated_partition.connect("clicked", self.on_button_generated_partition_clicked, "Generated")
		self.button_similarity.connect("clicked", self.on_button_similarity_clicked)
		self.button_external_validation.connect("clicked", self.on_button_external_validation_clicked)
		self.button_internal_validation.connect("clicked", self.on_button_internal_validation_clicked)
		self.button_algorithm.connect("clicked", self.on_button_algorithm_clicked)
		self.button_execute.connect("clicked", self.on_button_execute_clicked)
		self.button_save.connect("clicked", self.on_button_save_clicked)
		self.button_open.connect("clicked", self.on_button_open_clicked)
		self.button_close.connect("clicked", self.on_button_close_clicked)

		# Associate the buttons to the containers
		self.bbox1.pack_start(self.button_dataset, True, True, 0)
		self.bbox1.pack_start(self.button_real_partition, True, True, 0)
		self.bbox1.pack_start(self.button_generated_partition, True, True, 0)
		self.bbox2.pack_start(self.button_similarity, True, True, 0)
		self.bbox2.pack_start(self.button_external_validation, True, True, 0)
		self.bbox2.pack_start(self.button_internal_validation, True, True, 0)
		self.bbox2.pack_start(self.button_algorithm, True, True, 0)

		self.bbox3.pack_start(self.button_execute, True, True, 0)
		self.bbox3.pack_start(self.button_save, True, True, 0)
		self.bbox3.pack_start(self.button_open, True, True, 0)
		self.bbox3.pack_start(self.button_close, True, True, 0)

		# Create the windows
		self.win_dataset = DataSetWindow();
		self.win_real_partition = RealPartitionWindow()
		self.win_generated_partition = GeneratedPartitionWindow()
		self.win_external_validation = ExternalValidationWindow()
		self.win_internal_validation = InternalValidationWindow()
		self.win_algorithm = AlgorithmWindow()
		self.win_similarity = SimilarityWindow()

	def on_button_dataset_clicked(self, widget):
		self.win_dataset.show_all()

	def on_button_real_partition_clicked(self, widget, data):
		self.win_dataset_list = self.win_dataset.get_selection_list()
		self.win_real_partition.set_dataset_list(self.win_dataset_list)
		self.win_real_partition.show_all()

	def on_button_generated_partition_clicked(self, widget, data):
		self.win_dataset_list = self.win_dataset.get_selection_list()
		self.win_generated_partition.set_dataset_list(self.win_dataset_list)
		self.win_generated_partition.show_all()

	def on_button_external_validation_clicked(self, widget):
		self.win_external_validation.show_all()
		
	def on_button_internal_validation_clicked(self, widget):
		self.win_internal_validation.show_all()
		
	def on_button_algorithm_clicked(self, widget):
		self.win_algorithm.show_all()

	def on_button_similarity_clicked(self, widget):
		self.win_similarity.show_all()

	def on_button_close_clicked(self, widget):
		Gtk.main_quit()

	def on_button_execute_clicked(self, widget):

		# instanciate Clex
		print ">> Creating Clex instance..."
		self.clex = Clex()
		print ">> Clex instance created."
		
		# instanciate Similarity Measures
		print ">> Setting Similarity measure..."
		self.win_similarity_list = self.win_similarity.get_selection_list()

		if(self.win_similarity_list == []):
			print ">> No Similarities selected."
			return;

		self.similarity_list = StrVector(len(self.win_similarity_list))
		for i in range(0, len(self.similarity_list)):
			self.similarity_list[i] = self.win_similarity_list[i]
		self.clex.setSimilarity(self.similarity_list)
		print ">> Similarity measures setted."

		# instanciate DataSets
		print ">> Loading DataSets..."
		self.win_dataset_list = self.win_dataset.get_selection_list()
		if(self.win_dataset_list == []):
			print ">> No DataSets selected."
			return;

		self.dataset_list = StrPairVector(len(self.win_dataset_list))
		for i in range(0, len(self.dataset_list)):
			# split directory name from the filename
			self.head, self.tail = path.split(self.win_dataset_list[i][0])
			# cut 'file://' off, convert unicode to bytecode, and create a pair of strings
			self.dataset_list[i] = StrPair(urlparse(self.head).path.encode() + '/', self.tail.encode())
	
		self.clex.setDataSet(self.dataset_list)
		print ">> DataSets loaded."

		# instanciate External Validation Indexes
		print ">> Setting External Validation Indexes..."
		self.win_external_validation_list = self.win_external_validation.get_selection_list()
		if(self.win_external_validation_list != []):
			self.external_validation_list = StrVector(len(self.win_external_validation_list))
			for i in range(0, len(self.external_validation_list)):
				self.external_validation_list[i] = self.win_external_validation_list[i]
			self.clex.setExternalIndex(self.external_validation_list)
		print ">> External Validation Indexes setted."

		# instanciate Internal Validation Indexes
		print ">> Setting Internal Validation Indexes..."
		self.win_internal_validation_list = self.win_internal_validation.get_selection_list()
		if(self.win_internal_validation_list != []):
			self.internal_validation_list = StrVector(len(self.win_internal_validation_list))
			for i in range(0, len(self.internal_validation_list)):
				self.internal_validation_list[i] = self.win_internal_validation_list[i]
			self.clex.setInternalIndex(self.internal_validation_list)
		print ">> Internal Validation Indexes setted."

		# Clustering program
		self.cluster_program = self.win_algorithm.get_call_string()

		# Prepare the calling string
		self.call_list = []
		self.win_algorithm_list = self.win_algorithm.get_selection_list()
		for algorithm in self.win_algorithm_list:
			print algorithm
			if (algorithm == "K-means"):
				for k in range(self.get_minK(), self.get_maxK() + 1):
					self.call_list.append([self.cluster_program, "-k", str(k)])

		for call_string in self.call_list:
			call(call_string)

	def on_button_save_clicked(self, widget):
		print 'on_button_save_clicked: not implemented yet' 

	def on_button_open_clicked(self, widget):
		print 'on_button_open_clicked: not implemented yet' 

	def get_minK(self):
		return self.spin_min_cluster.get_value_as_int()

	def get_maxK(self):
		return self.spin_max_cluster.get_value_as_int()

win = MainWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()
