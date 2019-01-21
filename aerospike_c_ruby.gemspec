Gem::Specification.new do |s|
  s.name        = 'aerospike_c_ruby'
  s.version     = '0.5.2'
  s.date        = '2019-01-21'
  s.summary     = "aerospike_c_ruby"
  s.description = "aerospike_c_ruby"
  s.authors     = ["Adam Stomski", "Arkadiusz Jasinski", "Herman Sadik"]
  s.email       = 'office@itelab.eu'

  s.files       = Dir["{lib}/**/*", "Rakefile", "README.md", 'ext/**/*.c', 'ext/**/*.h']
  s.test_files  = Dir["spec/**/*"]
  s.extensions = %w[ext/aerospike_c_ruby/extconf.rb]

  s.license = 'MIT'
end
