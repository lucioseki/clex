from ValidationWindow import *

class ExternalValidationWindow(ValidationWindow):
	def __init__(self):
		ValidationWindow.__init__(self, "External")
		self.store.append(["CRIndex"])
		self.store.append(["NMIIndex"])
		self.store.append(["VIIndex"])
