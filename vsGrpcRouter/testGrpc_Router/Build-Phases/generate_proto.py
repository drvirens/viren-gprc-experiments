#!/Library/Frameworks/Python.framework/Versions/3.6/bin/python3.6

import subprocess
import sys


class c_proto:
	def __init__(self):
		print("__init__")

		self.is_protoc_installed = False
		self.is_min_protoc_ver = False
		self.version = ""


	def quit(self):
		sys.exit()


	def debug_print(self, str):
		print(str)


	def has_protoc(self):
		self.debug_print("has_protoc")

		str_cmd_output = ""
		try:
			raw_cmd_output = subprocess.check_output(["protoc"], stderr=subprocess.DEVNULL)
			str_cmd_output = raw_cmd_output.decode("utf-8")
			if len(str_cmd_output) > 6:
				self.debug_print("aha - found protoc")
				self.is_protoc_installed = True
			else:
				self.quit()

		except subprocess.CalledProcessError as exception:
			print("error: protoc not found")
			self.is_protoc_installed = False
			self.quit()

		return self.is_protoc_installed


	def is_protoc_above_expected_version(self):
		self.debug_print("is_protoc_above_expected_version")

		str_cmd_output = ""
		try:
			raw_cmd_output = subprocess.check_output(["protoc", "--version"], stderr=subprocess.DEVNULL)
			str_cmd_output = raw_cmd_output.decode("utf-8")
			if len(str_cmd_output) > 6:
				self.debug_print("version of protoc: " + str_cmd_output)

				tokens = str_cmd_output.split()
				protoc_version = tokens[1]

				if protoc_version.startswith("3."):
					self.is_min_protoc_ver = True
					self.debug_print("Has min expected protoc version")

			else:
				self.quit()

		except subprocess.CalledProcessError as exception:
			self.debug_print("error: protoc not found")
			self.is_min_protoc_ver = False
			self.quit()

		return self.is_min_protoc_ver


	def generate(self):
		""" generate protoc classes

		protoc  -I=./ --cpp_out=./testGrpc_Router/gen ./proto/router.proto
		"""
		self.debug_print("generate")

		try: 
			srcroot = "${SRCROOT}"
			self.debug_print(srcroot)


			raw_cmd_output = subprocess.run(["protoc", "-I=./", "--cpp_out=./testGrpc_Router/gen", "./proto/router.proto"])
			#raw_cmd_output = subprocess.run(["protoc", "-I=${PROJECT_DIR}", "--cpp_out=./testGrpc_Router/gen", "./proto/router.proto"])
		except subprocess.CalledProcessError as exception:
			self.debug_print("ERROR: could not execute cmd")
		except:
			self.debug_print("some other error")
		

	def run(self):
		""" Run protoc command
		
		Generate proto files. Command is like below:
			> protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto

		More details at:
		https://developers.google.com/protocol-buffers/docs/cpptutorial
		"""

		self.debug_print("run")
		if self.has_protoc():
			if self.is_protoc_above_expected_version():
				self.generate()
		else:
			pass



def main():
	print("boot start")
	obj_proto = c_proto()
	obj_proto.run()
	print("boot end")




if __name__ == "__main__":
	main()

